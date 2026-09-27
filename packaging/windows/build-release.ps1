param(
    [string]$Version = "0.1.0",
    [switch]$SkipBuild
)

$ErrorActionPreference = "Stop"
$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$InstallDir = Join-Path $RepoRoot "install"
$DistDir = Join-Path $RepoRoot "dist"
$InstallerScript = Join-Path $PSScriptRoot "PrismModernUI.iss"

Push-Location $RepoRoot
try {
    if (-not $SkipBuild) {
        Write-Host "Building Release..." -ForegroundColor Cyan
        cmake --build --preset windows_msvc --config Release
        if ($LASTEXITCODE -ne 0) { throw "Release build failed." }

        Write-Host "Creating self-contained install bundle..." -ForegroundColor Cyan
        cmake --install build --config Release
        if ($LASTEXITCODE -ne 0) { throw "Install/bundle step failed." }
    }

    $LauncherExe = Join-Path $InstallDir "prismlauncher.exe"
    if (-not (Test-Path $LauncherExe)) {
        throw "Missing $LauncherExe. Build/install the Release bundle first."
    }

    New-Item -ItemType Directory -Force -Path $DistDir | Out-Null

    $ZipPath = Join-Path $DistDir "Prism-Modern-UI-Portable-$Version.zip"
    if (Test-Path $ZipPath) { Remove-Item $ZipPath -Force }

    Write-Host "Creating portable ZIP..." -ForegroundColor Cyan
    Compress-Archive -Path (Join-Path $InstallDir "*") -DestinationPath $ZipPath -CompressionLevel Optimal

    $Candidates = @(
        @(
            (Join-Path $env:LOCALAPPDATA "Programs\Inno Setup 6\ISCC.exe"),
            (Join-Path ${env:ProgramFiles(x86)} "Inno Setup 6\ISCC.exe"),
            (Join-Path $env:ProgramFiles "Inno Setup 6\ISCC.exe")
        ) | Where-Object { $_ -and (Test-Path $_) }
    )

    $Iscc = $null
    if ($Candidates.Count -gt 0) {
        $Iscc = [string]$Candidates[0]
    } else {
        $Command = Get-Command ISCC.exe -ErrorAction SilentlyContinue
        if ($Command) { $Iscc = $Command.Source }
    }

    if (-not $Iscc) {
        Write-Warning "Inno Setup 6 was not found. The portable ZIP was created, but the installer was not."
        Write-Host "Install Inno Setup 6, then run this script again with -SkipBuild." -ForegroundColor Yellow
        Write-Host "Portable ZIP: $ZipPath" -ForegroundColor Green
        exit 0
    }

    Write-Host "Building Windows installer..." -ForegroundColor Cyan
    & $Iscc "/DMyAppVersion=$Version" $InstallerScript
    if ($LASTEXITCODE -ne 0) { throw "Inno Setup compilation failed." }

    $SetupPath = Join-Path $DistDir "Prism-Modern-UI-Setup-$Version.exe"
    Write-Host ""
    Write-Host "Release package complete." -ForegroundColor Green
    Write-Host "Installer:    $SetupPath"
    Write-Host "Portable ZIP: $ZipPath"
}
finally {
    Pop-Location
}
