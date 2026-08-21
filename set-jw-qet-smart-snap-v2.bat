@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"
set "CMAKE=C:\msys64\ucrt64\bin\cmake.exe"
set "BUILD_DIR=%REPO%\build\jw-qet-dev"

if /I "%~1"=="on" goto enable
if /I "%~1"=="off" goto disable

echo Uso:
echo   %~nx0 on
echo   %~nx0 off
echo.
echo Smart Snap V2 permanece opt-in mientras terminamos su validacion.
exit /b 2

:check
if not exist "%CMAKE%" (
    echo [ERROR] No se encontro CMake UCRT64:
    echo         %CMAKE%
    exit /b 1
)
if not exist "%BUILD_DIR%\CMakeCache.txt" (
    echo [ERROR] Aun no existe el build de desarrollo.
    echo Abre JW-QET-Launcher.exe una vez y vuelve a ejecutar este comando.
    exit /b 1
)
exit /b 0

:enable
call :check
if errorlevel 1 exit /b 1
echo [JW QET] Habilitando Smart Snap V2 solo para este build...
"%CMAKE%" -S "%REPO%" -B "%BUILD_DIR%" -DJW_QET_ENABLE_SMART_SNAP=ON
if errorlevel 1 exit /b 1
echo [OK] Smart Snap V2 habilitado.
echo Abre JW-QET-Launcher.exe para compilar y ejecutar.
exit /b 0

:disable
call :check
if errorlevel 1 exit /b 1
echo [JW QET] Deshabilitando Smart Snap V2...
"%CMAKE%" -S "%REPO%" -B "%BUILD_DIR%" -DJW_QET_ENABLE_SMART_SNAP=OFF
if errorlevel 1 exit /b 1
echo [OK] Smart Snap V2 deshabilitado.
echo Abre JW-QET-Launcher.exe para compilar y ejecutar.
exit /b 0
