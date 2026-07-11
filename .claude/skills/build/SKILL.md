---
name: build
description: This skill should be used whenever the user asks to build, compile, or check that WonderGirl compiles, or when you yourself need to verify a code change builds before reporting it done. Runs scripts/build.ps1, which locates MSBuild via vswhere and builds WonderGirl.sln, instead of re-discovering the MSBuild path or invoking msbuild by hand each time.
version: 0.1.0
---

# Build WonderGirl

Run `scripts/build.ps1` from the repo root via the PowerShell tool. It locates MSBuild through `vswhere.exe` (no hardcoded install path), builds `WonderGirl.sln`, and prints the path to the resulting exe.

```powershell
& "D:\Development\WonderGirl\WonderGirl\scripts\build.ps1"
```

Defaults to `Configuration=Debug Platform=x64` (the only platform currently wired up with SDL include/lib paths in the vcxproj — `Win32` will fail until that's added). Override with `-Configuration Release` and/or `-Platform Win32` if needed.

Pass `-Run` to launch the built exe immediately after a successful build:

```powershell
& "D:\Development\WonderGirl\WonderGirl\scripts\build.ps1" -Run
```

The script throws (non-zero exit) on any MSBuild failure, so a clean run with no thrown error means the build succeeded — no need to grep output for "error".
