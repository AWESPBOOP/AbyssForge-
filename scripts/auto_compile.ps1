param(
    [string]$BuildDir,
    [string]$BuildType
)

$ErrorActionPreference = 'Stop'

$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$rootDir = Resolve-Path (Join-Path $scriptRoot '..')

if (-not $BuildDir -or $BuildDir.Trim() -eq '') {
    $BuildDir = Join-Path $rootDir 'build'
}

if (-not $BuildType -or $BuildType.Trim() -eq '') {
    if ($env:CMAKE_BUILD_TYPE -and $env:CMAKE_BUILD_TYPE.Trim() -ne '') {
        $BuildType = $env:CMAKE_BUILD_TYPE
    } else {
        $BuildType = 'Release'
    }
}

Write-Host "[abyssforge] Configuring build directory: $BuildDir"
& cmake -S $rootDir -B $BuildDir -DCMAKE_BUILD_TYPE=$BuildType -DABYSSFORGE_BUILD_TESTS=OFF
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "[abyssforge] Building targets (configuration: $BuildType)"
& cmake --build $BuildDir --config $BuildType
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "[abyssforge] Build artifacts located in: $BuildDir"
