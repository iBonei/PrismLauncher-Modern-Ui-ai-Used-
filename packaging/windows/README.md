# Windows release packaging

This folder contains packaging for the unofficial Prism Modern UI fork.

## Build a local release

From an **x64 Native Tools Command Prompt for VS 2022** at the repository root:

```powershell
powershell -ExecutionPolicy Bypass -File .\packaging\windows\build-release.ps1 -Version 0.1.0
```

The script builds the MSVC Release configuration, runs CMake's install/bundle step, creates a portable ZIP in `dist\`, and creates a Windows installer with Inno Setup 6 when `ISCC.exe` is available.

If Inno Setup is not installed yet, the ZIP is still produced. After installing Inno Setup 6, rerun:

```powershell
powershell -ExecutionPolicy Bypass -File .\packaging\windows\build-release.ps1 -Version 0.1.0 -SkipBuild
```

Outputs:

- `dist\Prism-Modern-UI-Setup-0.1.0.exe`
- `dist\Prism-Modern-UI-Portable-0.1.0.zip`

## Distribution note

This is an unofficial modified fork of Prism Launcher and is not endorsed by or affiliated with the Prism Launcher project. Before publishing binaries publicly, review Prism Launcher's redistribution policy in the repository README and make sure fork-specific API keys/identifiers and licensing requirements are handled.
