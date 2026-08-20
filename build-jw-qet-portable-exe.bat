@echo off
setlocal EnableExtensions

title JW QET - Portable Builder Qt5 UCRT64

rem ============================================================
rem JW Control - QElectroTech portable build helper
rem Compatible con CMD clasico: ASCII, sin BOM.
rem ============================================================

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"

set "MSYS_ROOT=C:\msys64"
set "BASH=%MSYS_ROOT%\usr\bin\bash.exe"
set "UCRT_BIN=%MSYS_ROOT%\ucrt64\bin"
set "WINDEPLOY=%UCRT_BIN%\windeployqt-qt5.exe"
set "OBJDUMP=%UCRT_BIN%\objdump.exe"
set "QTSVG=%UCRT_BIN%\Qt5Svg.dll"
set "QTPDF=%UCRT_BIN%\Qt5Pdf.dll"
set "PACKAGER=%REPO%\packaging\windows\build-portable-package.ps1"

echo ============================================================
echo   JW QET - Portable Builder
echo ============================================================
echo.
echo Repo:
echo   %REPO%
echo.

if not exist "%PACKAGER%" (
    echo [ERROR] No se encontro:
    echo         %PACKAGER%
    echo.
    echo Coloca este BAT en la raiz de qelectrotech-source-mirror.
    pause
    exit /b 1
)

if not exist "%BASH%" (
    echo [ERROR] No se encontro MSYS2:
    echo         %BASH%
    echo.
    echo Instala primero MSYS2 en C:\msys64.
    pause
    exit /b 1
)

echo [1/5] Actualizando base de datos de paquetes...
"%BASH%" -lc "pacman -Sy --noconfirm"
if errorlevel 1 (
    echo.
    echo [ERROR] No se pudo actualizar la base de datos de pacman.
    pause
    exit /b 1
)

echo.
echo [2/5] Instalando / verificando dependencias UCRT64...
echo.

"%BASH%" -lc "pacman -S --needed --noconfirm mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-binutils mingw-w64-ucrt-x86_64-qt5-base mingw-w64-ucrt-x86_64-qt5-svg mingw-w64-ucrt-x86_64-qt5-tools mingw-w64-ucrt-x86_64-qt5-translations mingw-w64-ucrt-x86_64-qt5-pdf mingw-w64-ucrt-x86_64-sqlite3 mingw-w64-ucrt-x86_64-kwidgetsaddons mingw-w64-ucrt-x86_64-kcoreaddons mingw-w64-ucrt-x86_64-angleproject"

if errorlevel 1 (
    echo.
    echo [ERROR] pacman no pudo completar las dependencias.
    echo.
    echo Si MSYS2 pide una actualizacion completa, abre:
    echo   MSYS2 UCRT64
    echo y ejecuta:
    echo   pacman -Syu
    echo.
    echo Luego vuelve a ejecutar este BAT.
    pause
    exit /b 1
)

echo.
echo [3/5] Verificando herramientas y DLL clave...
echo.

set "FAILED=0"

if exist "%WINDEPLOY%" (
    echo [OK] windeployqt-qt5.exe
) else (
    echo [FALTA] %WINDEPLOY%
    set "FAILED=1"
)

if exist "%OBJDUMP%" (
    echo [OK] objdump.exe
) else (
    echo [FALTA] %OBJDUMP%
    set "FAILED=1"
)

if exist "%QTSVG%" (
    echo [OK] Qt5Svg.dll
) else (
    echo [FALTA] %QTSVG%
    set "FAILED=1"
)

if exist "%QTPDF%" (
    echo [OK] Qt5Pdf.dll
) else (
    echo [WARN] Qt5Pdf.dll no encontrada en la ruta esperada.
)

if "%FAILED%"=="1" (
    echo.
    echo [ERROR] El entorno UCRT64 sigue incompleto.
    pause
    exit /b 1
)

echo.
echo [4/5] Preparando PATH temporal...
set "PATH=%UCRT_BIN%;%PATH%"
echo [OK] %UCRT_BIN%
echo.

echo [5/5] Ejecutando empaquetador...
echo.

if "%~1"=="" (
    echo OutputRoot:
    echo   build\p
    echo.
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PACKAGER%" -OutputRoot "build\p"
) else (
    echo Argumentos personalizados:
    echo   %*
    echo.
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PACKAGER%" %*
)

set "RC=%ERRORLEVEL%"

echo.
if not "%RC%"=="0" (
    echo ============================================================
    echo   BUILD PORTABLE FALLIDO - codigo %RC%
    echo ============================================================
    echo.
    pause
    exit /b %RC%
)

echo ============================================================
echo   BUILD PORTABLE COMPLETADO
echo ============================================================
echo.
echo Revisa:
echo   %REPO%\build\p
echo.
pause
exit /b 0
