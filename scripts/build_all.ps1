param(
    [string]$BuildDir,
    [string[]]$ConfigureArgs
)

$ErrorActionPreference = 'Stop'

$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$rootDir = Resolve-Path (Join-Path $scriptRoot '..')

if (-not $BuildDir -or $BuildDir.Trim() -eq '') {
    $BuildDir = Join-Path $rootDir 'build'
}

$cmakeArgs = @('-S', $rootDir, '-B', $BuildDir, '-DABYSSFORGE_BUILD_TESTS=ON')
if ($ConfigureArgs) {
    $cmakeArgs += $ConfigureArgs
}

& cmake @cmakeArgs
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& cmake --build $BuildDir
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& ctest --test-dir $BuildDir
exit $LASTEXITCODE
