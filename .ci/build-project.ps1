$ErrorActionPreference="Stop"

$VCPKG_DIR=$args[0]
$BUILD_DIR=$args[1]

if ($null -eq $BUILD_DIR) { $BUILD_DIR="build" }

Write-Host "---- build-project.ps1 ----"
Write-Host "BUILD_DIR: $BUILD_DIR"
Write-Host "CMAKE_TOOLCHAIN_FILE: $TOOLCHAIN"
Write-Host "---------------------------"

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    New-Alias -Name cmake -Value "$Env:ProgramFiles\CMake\bin\cmake.exe"
}

New-Item -Name $BUILD_DIR -ItemType Directory
Push-Location $BUILD_DIR
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
Pop-Location