@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
set "PACKAGER=%REPO%packaging\windows\invoke-portable-package.ps1"

if not exist "%PACKAGER%" (
    echo [ERROR] No se encontro:
    echo         %PACKAGER%
    exit /b 1
)

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PACKAGER%" ^
  -BuildDir "build\jw-qet-qt5-nokf" ^
  -OutputRoot "build\p" ^
  -ReleaseDir "release" %*

exit /b %ERRORLEVEL%
