# WonderGirl

A 2D platformer built in C++ with SDL3, primarily as a learning project (game dev + C++). Jump/run mechanics are implemented; character rendering uses sprites and animation frames.

## Tech stack

- C++17, CMake (3.20+)
- SDL3, SDL3_image, SDL3_ttf — vendored as git submodules under `external/`, built locally into `external/<lib>/build-mac`
- Entry point: [WonderGirl.cpp](WonderGirl.cpp) → [Application.h](Application.h)/[Application.cpp](Application.cpp) owns the SDL window/renderer and main loop; [Character.h](Character.h)/[Character.cpp](Character.cpp) and [Sprite.h](Sprite.h)/[Sprite.cpp](Sprite.cpp) handle the player entity and rendering; [Animation.h](Animation.h)/[Animation.cpp](Animation.cpp) handles frame sequencing

## Development environment

- Primary: macOS, VS Code
- Build (Mac): `scripts/build.sh` — wraps `cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=<Debug|Release> -DCMAKE_EXPORT_COMPILE_COMMANDS=ON` + `cmake --build build -j8` (matches `.vscode/tasks.json`'s default build task). Flags: `-Configuration Debug|Release`, `-Run` to launch after building.
- Build (Windows): `scripts/build.ps1` — locates MSBuild via `vswhere` and builds `WonderGirl.sln`. Kept for a Windows dev on the project; not the path used day-to-day here.
- Run from repo root — assets are loaded via paths relative to the working directory (e.g. `assets/Tom-Tom.png`)
- Debugging: lldb-dap via `.vscode/launch.json` ("Debug WonderGirl")

## Working with Claude on this project

- User is a junior developer working with assistance from a senior dev on the team — explain game-dev/engine concepts briefly as they come up, but keep responses brief by default; go deeper only if told something isn't understood.
- Keep changes minimal and incremental — prefer small, focused diffs over larger restructuring even if a bigger refactor looks cleaner.
- Always build before calling a change done — use `scripts/build.sh` on this (Mac) environment.
