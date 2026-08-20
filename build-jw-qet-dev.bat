@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"
set "MSYS_ROOT=C:\msys64"
set "UCRT_BIN=%MSYS_ROOT%\ucrt64\bin"
set "PATH=%UCRT_BIN%;%PATH%"
set "CMAKE=%UCRT_BIN%\cmake.exe"
set "NINJA=%UCRT_BIN%\ninja.exe"
set "BUILD_DIR=%REPO%\build\jw-qet-dev"

set "BUILD_TYPE=RelWithDebInfo"
if defined JW_QET_BUILD_TYPE set "BUILD_TYPE=%JW_QET_BUILD_TYPE%"

if /I "%~1"=="--clean" (
    echo [JW QET] Limpiando build de desarrollo...
    if exist "%BUILD_DIR%" rmdir /S /Q "%BUILD_DIR%"
    shift
)

if not exist "%CMAKE%" (
    echo [ERROR] No se encontro CMake UCRT64:
    echo         %CMAKE%
    echo.
    echo Ejecuta primero:
    echo   setup-jw-qet-dev-environment.bat
    exit /b 1
)

if not exist "%NINJA%" (
    echo [ERROR] No se encontro Ninja UCRT64:
    echo         %NINJA%
    echo.
    echo Ejecuta primero:
    echo   setup-jw-qet-dev-environment.bat
    exit /b 1
)

if not exist "%REPO%\elements" (
    echo [ERROR] No se encontro el submodulo elements.
    echo Ejecuta:
    echo   git submodule update --init --recursive
    exit /b 1
)

echo ============================================================
echo   JW QET - Build de desarrollo
echo ============================================================
echo Build type : %BUILD_TYPE%
echo Build dir  : %BUILD_DIR%
echo.

if not exist "%BUILD_DIR%\CMakeCache.txt" (
    echo [1/2] Configurando CMake...
    "%CMAKE%" -S "%REPO%" -B "%BUILD_DIR%" -G Ninja ^
      -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
      -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 ^
      -DQt5_DIR=C:/msys64/ucrt64/lib/cmake/Qt5 ^
      -DQT_VERSION_MAJOR=5 ^
      -DCMAKE_DISABLE_FIND_PACKAGE_Qt6=ON ^
      -DPACKAGE_TESTS=OFF ^
      -DCMAKE_POLICY_DEFAULT_CMP0077=NEW ^
      -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ^
      -DQET_EXPORT_PROJECT_DB=ON ^
      -DSQLite3_INCLUDE_DIR=C:/msys64/ucrt64/include ^
      -DSQLite3_LIBRARY=C:/msys64/ucrt64/lib/libsqlite3.dll.a

    if errorlevel 1 (
        echo [ERROR] Fallo la configuracion CMake.
        exit /b 1
    )
) else (
    echo [1/2] CMake ya configurado. Se reutiliza el cache.
)

echo.
echo [2/2] Compilando incrementalmente...
"%CMAKE%" --build "%BUILD_DIR%" --parallel

if errorlevel 1 (
    echo [ERROR] Fallo la compilacion.
    exit /b 1
)

if not exist "%BUILD_DIR%\qelectrotech.exe" (
    echo [ERROR] La compilacion termino pero no existe:
    echo         %BUILD_DIR%\qelectrotech.exe
    exit /b 1
)

echo.
echo [OK] Build de desarrollo listo:
echo      %BUILD_DIR%\qelectrotech.exe
exit /b 0
