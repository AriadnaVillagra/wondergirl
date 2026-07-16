---
name: build
description: This skill should be used whenever the user asks to build, compile, or check that WonderGirl compiles, or when you yourself need to verify a code change builds before reporting it done. Runs the platform-appropriate build script (scripts/build.sh on Mac/Linux via CMake, scripts/build.ps1 on Windows via MSBuild), instead of re-discovering the build steps or invoking cmake/msbuild by hand each time.
version: 0.2.0
---

# Build WonderGirl

Pick the script for the current OS — both accept `-Configuration Debug|Release` (default `Debug`) and `-Run` to launch the built game immediately after a successful build.

## macOS / Linux

Run `scripts/build.sh` from the repo root via Bash. It configures with CMake (`Unix Makefiles`) into `build/`, builds with `cmake --build`, and prints the path to the resulting binary.

```bash
./scripts/build.sh
```

```bash
./scripts/build.sh -Configuration Release -Run
```

Exits non-zero (via `set -euo pipefail`) on any CMake/build failure, so a clean run with no error means the build succeeded — no need to grep output for "error".

## Windows

Run `scripts/build.ps1` from the repo root via the PowerShell tool. It locates MSBuild through `vswhere.exe` (no hardcoded install path), builds `WonderGirl.sln`, and prints the path to the resulting exe.

```powershell
& "D:\Development\WonderGirl\WonderGirl\scripts\build.ps1"
```

Defaults to `Configuration=Debug Platform=x64` (the only platform currently wired up with SDL include/lib paths in the vcxproj — `Win32` will fail until that's added). Override with `-Configuration Release` and/or `-Platform Win32` if needed.

```powershell
& "D:\Development\WonderGirl\WonderGirl\scripts\build.ps1" -Run
```

The script throws (non-zero exit) on any MSBuild failure, so a clean run with no thrown error means the build succeeded — no need to grep output for "error".
