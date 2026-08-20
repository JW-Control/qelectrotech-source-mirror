@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"
set "MSYS_ROOT=C:\msys64"
set "UCRT_BIN=%MSYS_ROOT%\ucrt64\bin"
set "PATH=%UCRT_BIN%;%PATH%"
set "CMAKE=%UCRT_BIN%\cmake.exe"
set "NINJA=%UCRT_BIN%\ninja.exe"
set "BUILD_DIR=%REPO%\build\jw-qet-qt5-nokf"

set "CLEAN_BUILD=0"
if /I "%~1"=="--clean" (
    set "CLEAN_BUILD=1"
    shift
)

if not "%~1"=="" (
    echo [ERROR] Opcion no reconocida: %~1
    echo Opcion soportada: --clean
    exit /b 2
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

if "%CLEAN_BUILD%"=="1" (
    echo [JW QET] Limpiando build Release...
    if exist "%BUILD_DIR%" rmdir /S /Q "%BUILD_DIR%"
)

rem CMakeCache.txt contiene rutas absolutas. Si el repo fue movido o
rem clonado en otra ubicacion, el cache anterior no puede reutilizarse.
if exist "%BUILD_DIR%\CMakeCache.txt" (
    findstr /L /I /X /C:"CMAKE_HOME_DIRECTORY:INTERNAL=%REPO:\=/%" "%BUILD_DIR%\CMakeCache.txt" >nul 2>&1
    if errorlevel 1 (
        echo [JW QET] Cache CMake de Release pertenece a otra ruta.
        echo [JW QET] Regenerando build Release automaticamente...
        rmdir /S /Q "%BUILD_DIR%"
    )
)

echo ============================================================
echo   JW QET - Build Release + Portable
echo ============================================================
echo.

if not exist "%BUILD_DIR%\CMakeCache.txt" (
    echo [1/3] Configurando Release...
    "%CMAKE%" -S "%REPO%" -B "%BUILD_DIR%" -G Ninja ^
      -DCMAKE_BUILD_TYPE=Release ^
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
        echo [ERROR] Fallo la configuracion Release.
        exit /b 1
    )
) else (
    echo [1/3] Configuracion Release existente.
)

echo.
echo [2/3] Compilando Release incrementalmente...
"%CMAKE%" --build "%BUILD_DIR%" --parallel
if errorlevel 1 (
    echo [ERROR] Fallo la compilacion Release.
    exit /b 1
)

echo.
echo [3/3] Generando artefactos portables...
call "%REPO%\package-jw-qet.bat"
if errorlevel 1 exit /b 1

echo.
echo ============================================================
echo   JW QET - BUILD COMPLETADO
 echo ============================================================
echo.
echo Artefactos finales:
echo   %REPO%\release
echo.
exit /b 0
