---
name: add-sdl-library
description: This skill should be used when the user asks to add, integrate, or wire up an SDL3 companion library (SDL_image, SDL_ttf, SDL_mixer, SDL_net, etc.) into WonderGirl. Captures the submodule-plus-CMake-plus-vcxproj recipe discovered while integrating SDL_image, instead of re-deriving it from scratch (finding the right CMake flags, MSBuild path, vcxproj sections) each time a new library is added.
version: 0.1.0
---

# Add an SDL3 companion library

WonderGirl vendors SDL3 as a git submodule (`external/SDL`) built as a static lib via
CMake + MSBuild, with `external/SDL/build/SDL3Config.cmake` as the package config other
libraries build against. Companion libraries (SDL_image, SDL_ttf, SDL_mixer, ...) follow
the same recipe. Below, `<Lib>` is the library name as used in its repo/CMake project
(e.g. `SDL_image`, `SDL_ttf`), `<PREFIX>` is its CMake option prefix (e.g. `SDLIMAGE`,
`SDLTTF` — check the library's `CMakeLists.txt` for `option(<PREFIX>_...` to find it).

## 1. Add the submodule, pinned to a stable release tag

```bash
git submodule add https://github.com/libsdl-org/<Lib>.git external/<Lib>
cd external/<Lib> && git tag --sort=-creatordate | head -20
```

Pick the newest `release-3.x.y` tag (skip `prerelease-`/`preview-` tags), matching how
`external/SDL` is pinned to a `release-3.x.y` tag rather than tracking a branch:

```bash
git checkout release-3.x.y
```

**Gotcha:** run `cd external/<Lib>` and the following git commands as separate steps and
confirm with `pwd` before doing anything relative-path-sensitive afterward. A failed `cd`
inside a `&&` chain silently no-ops the rest of the chain, and it's easy to end up running
later commands from the wrong directory without noticing.

Then `cd` back to the repo root (verify with `pwd`) before continuing.

## 2. Decide which optional vendored dependencies to skip

Read `external/<Lib>/CMakeLists.txt` for `option(<PREFIX>_...` lines. These libraries
bundle format/codec-specific submodules under `external/<Lib>/external/` (e.g. SDL_image
vendors zlib, libpng, libwebp, libtiff, libavif, dav1d, aom, libjxl for its various image
formats). Building all of them is slow and usually unnecessary.

- Look for a top-level `<PREFIX>_VENDORED` option — set it `OFF` to stop CMake from
  requiring those nested submodules to be checked out.
- Check whether the feature you actually need has a dependency-free fallback. SDL_image's
  PNG/JPEG loading works through a bundled `stb_image` backend (`SDLIMAGE_BACKEND_STB`,
  default `ON`) with **no** libpng/zlib needed — this was found by grepping the library's
  CMakeLists for `STB` and reading `src/IMG_png.c`'s load path
  (`IMG_LoadPNG_IO`: tries libpng if compiled in, else Windows WIC, else falls back to a
  minimal in-SDL3 loader). When a CMake configure fails with "Could not find CMakeLists.txt
  for `<dep>`... run the download script or re-configure with `<PREFIX>_VENDORED=OFF`",
  that confirms the dependency isn't load-bearing for the format you need.
- Explicitly disable heavy formats/features you don't need via their per-feature flags
  (e.g. `-DSDLIMAGE_AVIF=OFF -DSDLIMAGE_JXL=OFF -DSDLIMAGE_WEBP=OFF -DSDLIMAGE_TIF=OFF`)
  so CMake doesn't even look for their vendored submodules.
- If a feature genuinely has no alternative backend (e.g. SDL_ttf's FreeType dependency
  for font rasterization — there's no fallback, unlike SDL_image's PNG/JPEG), you'll need
  to actually pull the nested submodule: `git submodule update --init external/<Lib>/external/<dep>`.
  Check first — `<PREFIX>_VENDORED=OFF` often lets CMake fall back to a `find_package`
  that just fails gracefully instead of hard-erroring, in which case no submodule init is
  needed at all.

## 3. Configure and build with CMake + MSBuild

Point the library at the already-built SDL3 package config, disable shared libs and
samples/tests:

```bash
cmake -S external/<Lib> -B external/<Lib>/build -G "Visual Studio 17 2022" -A x64 \
  -DSDL3_DIR="$(pwd)/external/SDL/build" \
  -DBUILD_SHARED_LIBS=OFF \
  -D<PREFIX>_VENDORED=OFF \
  -D<PREFIX>_SAMPLES=OFF \
  -D<PREFIX>_TESTS=OFF \
  [... feature flags from step 2]
```

Read the tail of the configure output — CMake prints an enabled/disabled backend summary
for these libraries (e.g. `SDL3_image backends: - enabled: stb ani bmp gif jpg ... - disabled: imageio wic avif jxl apng tif webp`).
Confirm what you expected to disable is actually disabled before building.

Then build both configs against the generated solution (reuse the MSBuild resolved by
[[build]]'s `scripts/build.ps1` — locate it via `vswhere.exe` rather than hardcoding a
path):

```powershell
$msbuild = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' | Select-Object -First 1
& $msbuild "external\<Lib>\build\<Lib>.sln" -p:Configuration=Debug -p:Platform=x64 -m -nologo -v:minimal
& $msbuild "external\<Lib>\build\<Lib>.sln" -p:Configuration=Release -p:Platform=x64 -m -nologo -v:minimal
```

## 4. Find what got built

```bash
find external/<Lib>/build/Debug external/<Lib>/build/Release -maxdepth 1 -iname "*.lib"
find external/<Lib>/include -maxdepth 2
```

Static-lib targets from these CMake projects are typically named `<Lib3>-static.lib`
(e.g. `SDL3_image-static.lib`, `SDL3_ttf-static.lib`).

**If step 2 required initializing a vendored nested submodule** (e.g. freetype for
SDL_ttf), that dependency builds as its own separate `.lib` under
`external/<Lib>/build/external/<dep>/<Config>/` — it is *not* folded into `<Lib>3-static.lib`
by the static-lib CMake target, so it must be added to `AdditionalLibraryDirectories`
and `AdditionalDependencies` alongside `<Lib>`'s own lib in step 5. Also don't assume the
Debug and Release filenames match: freetype's own CMakeLists names its Debug output
`freetyped.lib` (with a `d` suffix) vs. `freetype.lib` in Release — check both
`find ... -maxdepth 1 -iname "*.lib"` outputs rather than assuming one name for both
configs.

## 5. Wire it into WonderGirl.vcxproj

`WonderGirl.vcxproj` only has SDL include/lib paths set up for the `Debug|x64` and
`Release|x64` configurations (Win32 isn't wired up at all). In **both** of those
`ItemDefinitionGroup`s:

- `ClCompile > AdditionalIncludeDirectories`: append `$(SolutionDir)external\<Lib>\include;`
- `Link > AdditionalLibraryDirectories`: append `$(SolutionDir)external\<Lib>\build\Debug;`
  (or `\Release` in the Release group)
- `Link > AdditionalDependencies`: prepend the new `.lib` filename before `SDL3-static.lib`

## 6. Ignore the build output, then verify

Add `external/<Lib>/build/` to `.gitignore` (next to the existing `external/SDL/build/`
entry), then run the [[build]] skill to confirm the solution still compiles and links
cleanly with the new library present.
