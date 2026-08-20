@echo off
setlocal EnableExtensions

rem Compatibility wrapper. Prefer package-jw-qet.bat for new workflows.
call "%~dp0package-jw-qet.bat" %*
exit /b %ERRORLEVEL%
