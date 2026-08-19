@echo off
setlocal

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0packaging\windows\build-portable-package.ps1" %*
exit /b %ERRORLEVEL%
