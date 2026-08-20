@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
set "BUILD_DIR=%REPO%build\jw-qet-dev"
set "EXE=%BUILD_DIR%\qelectrotech.exe"
set "MSYS_ROOT=C:\msys64"
set "UCRT_BIN=%MSYS_ROOT%\ucrt64\bin"
set "QT_PLUGIN_PATH=%MSYS_ROOT%\ucrt64\share\qt5\plugins"
set "QT_QPA_PLATFORM_PLUGIN_PATH=%QT_PLUGIN_PATH%\platforms"

set "SKIP_BUILD=0"
set "CLEAN_BUILD=0"
set "QT_DEBUG=0"

:parse_options
if "%~1"=="" goto options_done
if /I "%~1"=="--no-build" (
    set "SKIP_BUILD=1"
    shift
    goto parse_options
)
if /I "%~1"=="--clean" (
    set "CLEAN_BUILD=1"
    shift
    goto parse_options
)
if /I "%~1"=="--qt-debug" (
    set "QT_DEBUG=1"
    shift
    goto parse_options
)

echo [ERROR] Opcion no reconocida: %~1
echo Opciones: --no-build, --clean, --qt-debug
exit /b 2

:options_done
if "%SKIP_BUILD%"=="0" (
    if "%CLEAN_BUILD%"=="1" (
        call "%REPO%build-jw-qet-dev.bat" --clean
    ) else (
        call "%REPO%build-jw-qet-dev.bat"
    )
    if errorlevel 1 exit /b 1
)

if not exist "%EXE%" (
    echo [ERROR] No existe el ejecutable de desarrollo:
    echo         %EXE%
    echo.
    echo Ejecuta sin --no-build para compilarlo.
    exit /b 1
)

if not exist "%UCRT_BIN%\Qt5Core.dll" (
    echo [ERROR] No se encontro el runtime Qt5 UCRT64.
    echo Ejecuta:
    echo   setup-jw-qet-dev-environment.bat
    exit /b 1
)

set "PATH=%UCRT_BIN%;%PATH%"
if "%QT_DEBUG%"=="1" set "QT_DEBUG_PLUGINS=1"

echo.
echo ============================================================
echo   JW QET - Ejecutando estado actual del repo
echo ============================================================
echo EXE      : %EXE%
echo Elements : %REPO%elements
echo Lang     : %REPO%lang
echo.
echo Cierra QElectroTech para volver a esta consola.
echo.

pushd "%REPO%"
"%EXE%" "--common-elements-dir=%REPO%elements" "--common-tbt-dir=%REPO%titleblocks" "--lang-dir=%REPO%lang"
set "RC=%ERRORLEVEL%"
popd

echo.
echo [JW QET] Proceso finalizado con codigo %RC%.
exit /b %RC%
