@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"

set "BUILD_DIR=%REPO%\build\jw-qet-dev"
set "EXE=%BUILD_DIR%\qelectrotech.exe"
set "MSYS_ROOT=C:\msys64"
set "UCRT_BIN=%MSYS_ROOT%\ucrt64\bin"
set "QT_PLUGIN_PATH=%MSYS_ROOT%\ucrt64\share\qt5\plugins"
set "QT_QPA_PLATFORM_PLUGIN_PATH=%QT_PLUGIN_PATH%\platforms"

set "SKIP_SYNC=0"
set "SKIP_BUILD=0"
set "CLEAN_BUILD=0"
set "QT_DEBUG=0"
set "DETACH=0"

:parse_options
if "%~1"=="" goto options_done
if /I "%~1"=="--no-pull" (
    set "SKIP_SYNC=1"
    shift
    goto parse_options
)
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
if /I "%~1"=="--detach" (
    set "DETACH=1"
    shift
    goto parse_options
)
if /I "%~1"=="--wait" (
    set "DETACH=0"
    shift
    goto parse_options
)

echo [ERROR] Opcion no reconocida: %~1
echo Opciones: --no-pull, --no-build, --clean, --qt-debug, --detach, --wait
exit /b 2

:options_done
if "%SKIP_SYNC%"=="0" (
    call :sync_repo
    if errorlevel 1 exit /b 1
) else (
    echo [JW QET] Sincronizacion Git omitida por --no-pull.
)

if "%SKIP_BUILD%"=="0" (
    if "%CLEAN_BUILD%"=="1" (
        call "%REPO%\build-jw-qet-dev.bat" --clean
    ) else (
        call "%REPO%\build-jw-qet-dev.bat"
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
echo Elements : %REPO%\elements
echo Lang     : %REPO%\lang
echo.

if "%DETACH%"=="1" (
    echo [JW QET] Iniciando QElectroTech en proceso independiente...
    pushd "%REPO%"
    start "" /D "%REPO%" "%EXE%" "--common-elements-dir=%REPO%\elements" "--common-tbt-dir=%REPO%\titleblocks" "--lang-dir=%REPO%\lang" >nul 2>&1
    if errorlevel 1 (
        popd
        echo [ERROR] Windows no pudo iniciar QElectroTech.
        exit /b 1
    )
    popd
    echo [OK] QElectroTech iniciado.
    exit /b 0
)

echo Cierra QElectroTech para volver a esta consola.
echo.

pushd "%REPO%"
"%EXE%" "--common-elements-dir=%REPO%\elements" "--common-tbt-dir=%REPO%\titleblocks" "--lang-dir=%REPO%\lang"
set "RC=%ERRORLEVEL%"
popd

echo.
echo [JW QET] Proceso finalizado con codigo %RC%.
exit /b %RC%

:sync_repo
where git.exe >nul 2>&1
if errorlevel 1 (
    echo [ERROR] No se encontro Git for Windows en PATH.
    echo Instala Git for Windows o ejecuta con --no-pull para usar el estado local.
    exit /b 1
)

pushd "%REPO%"
git rev-parse --is-inside-work-tree >nul 2>&1
if errorlevel 1 (
    echo [ERROR] La carpeta no parece ser un repositorio Git:
    echo         %REPO%
    popd
    exit /b 1
)

echo ============================================================
echo   JW QET - Sincronizando repositorio
echo ============================================================
echo.

set "DIRTY=0"
set "STASHED=0"
for /f "delims=" %%I in ('git status --porcelain --untracked-files=normal') do set "DIRTY=1"

if "%DIRTY%"=="1" (
    echo [JW QET] Hay cambios locales. Guardando stash temporal...
    git stash push -u -m "JW QET auto-sync"
    if errorlevel 1 (
        echo [ERROR] No se pudieron guardar temporalmente los cambios locales.
        popd
        exit /b 1
    )
    set "STASHED=1"
)

git pull --ff-only
if errorlevel 1 (
    echo.
    echo [ERROR] No se pudo actualizar el repositorio con fast-forward.
    echo         No se compilara una version potencialmente desactualizada.
    if "%STASHED%"=="1" (
        echo [JW QET] Restaurando cambios locales...
        git stash pop
    )
    echo.
    echo Para trabajar sin sincronizar usa:
    echo   run-jw-qet-dev.bat --no-pull
    popd
    exit /b 1
)

echo.
echo [JW QET] Sincronizando submodulos...
git submodule update --init --recursive
if errorlevel 1 (
    echo [ERROR] No se pudieron sincronizar los submodulos.
    if "%STASHED%"=="1" (
        echo [JW QET] Restaurando cambios locales...
        git stash pop
    )
    popd
    exit /b 1
)

if "%STASHED%"=="1" (
    echo.
    echo [JW QET] Restaurando tus cambios locales sobre la version actualizada...
    git stash pop
    if errorlevel 1 (
        echo.
        echo [ERROR] Hubo conflictos al restaurar tus cambios locales.
        echo         QElectroTech no se iniciara hasta resolverlos.
        echo         El stash se conserva cuando git stash pop falla por conflicto.
        popd
        exit /b 1
    )
)

echo.
echo [OK] Repositorio sincronizado.
echo.
popd
exit /b 0
