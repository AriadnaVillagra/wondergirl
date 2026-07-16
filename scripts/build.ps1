param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug",

    [ValidateSet("x64", "Win32")]
    [string]$Platform = "x64",

    [switch]$Run
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
$solution = Join-Path $repoRoot "WonderGirl.sln"

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
    throw "vswhere.exe not found at '$vswhere' - is Visual Studio installed?"
}

$msbuild = & $vswhere -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe | Select-Object -First 1
if (-not $msbuild) {
    throw "Could not locate MSBuild.exe via vswhere"
}

& $msbuild $solution "-p:Configuration=$Configuration" "-p:Platform=$Platform" -m -nologo -v:minimal
if ($LASTEXITCODE -ne 0) {
    throw "Build failed with exit code $LASTEXITCODE"
}

$exe = Join-Path $repoRoot "$Platform\$Configuration\WonderGirl.exe"
Write-Host "Build succeeded: $exe"

if ($Run) {
    & $exe
}
