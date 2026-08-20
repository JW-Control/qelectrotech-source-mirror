@echo off
setlocal EnableExtensions

title JW QET - Setup Windows Development Environment

set "REPO=%~dp0"
set "MSYS_ROOT=C:\msys64"
set "BASH=%MSYS_ROOT%\usr\bin\bash.exe"
set "INSTALLER=%TEMP%\msys2-x86_64-latest.exe"
set "MSYS_URL=https://repo.msys2.org/distrib/msys2-x86_64-latest.exe"

echo ============================================================
echo   JW QET - Setup de entorno Windows
echo ============================================================
echo.
echo Este script prepara:
echo   - MSYS2 UCRT64
echo   - GCC, CMake, Ninja y binutils
echo   - Qt5 y modulos usados por QElectroTech
echo   - KDE Frameworks requeridos
echo   - 7-Zip para empaquetado
echo   - JW-QET-Launcher.exe para uso normal sin consola
echo.

net session >nul 2>&1
if not "%ERRORLEVEL%"=="0" (
    echo [INFO] Solicitando permisos de Administrador...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process -FilePath '%~f0' -Verb RunAs"
    exit /b
)

if not exist "%BASH%" (
    echo [1/6] Descargando MSYS2...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ^
      "$ErrorActionPreference='Stop'; Invoke-WebRequest -Uri '%MSYS_URL%' -OutFile '%INSTALLER%'"
    if errorlevel 1 (
        echo [ERROR] No se pudo descargar MSYS2.
        pause
        exit /b 1
    )

    echo [2/6] Instalando MSYS2 en %MSYS_ROOT%...
    "%INSTALLER%" in --confirm-command --accept-messages --root C:/msys64
    if errorlevel 1 (
        echo [ERROR] Fallo la instalacion de MSYS2.
        pause
        exit /b 1
    )
) else (
    echo [1/6] MSYS2 ya esta instalado.
    echo [2/6] No es necesario reinstalarlo.
)

if not exist "%BASH%" (
    echo [ERROR] No se encontro bash despues de instalar MSYS2:
    echo         %BASH%
    pause
    exit /b 1
)

echo [3/6] Actualizando MSYS2...
"%BASH%" -lc "pacman -Syu --noconfirm"
if errorlevel 1 (
    echo [WARN] Primera pasada de actualizacion devolvio error.
    echo        Se intentara una segunda pasada.
)
"%BASH%" -lc "pacman -Syu --noconfirm"
if errorlevel 1 (
    echo [ERROR] No se pudo actualizar MSYS2.
    pause
    exit /b 1
)

echo.
echo [4/6] Instalando dependencias UCRT64...
"%BASH%" -lc "pacman -S --needed --noconfirm git mingw-w64-ucrt-x86_64-ccache mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-binutils mingw-w64-ucrt-x86_64-qt5-base mingw-w64-ucrt-x86_64-qt5-svg mingw-w64-ucrt-x86_64-qt5-tools mingw-w64-ucrt-x86_64-qt5-translations mingw-w64-ucrt-x86_64-qt5-pdf mingw-w64-ucrt-x86_64-sqlite3 mingw-w64-ucrt-x86_64-pkgconf mingw-w64-ucrt-x86_64-kwidgetsaddons mingw-w64-ucrt-x86_64-kcoreaddons mingw-w64-ucrt-x86_64-extra-cmake-modules mingw-w64-ucrt-x86_64-nsis mingw-w64-ucrt-x86_64-angleproject mingw-w64-ucrt-x86_64-7zip"

if errorlevel 1 (
    echo [ERROR] No se pudieron instalar las dependencias UCRT64.
    pause
    exit /b 1
)

if not exist "%REPO%.git" goto after_submodules

echo.
echo [INFO] Sincronizando submodulos del repositorio con Git for Windows...
where git.exe >nul 2>&1
if errorlevel 1 (
    echo [WARN] No se encontro Git for Windows en PATH.
    echo        Ejecuta luego: git submodule update --init --recursive
    goto after_submodules
)

git.exe -C "%REPO%." submodule update --init --recursive
if errorlevel 1 (
    echo [WARN] No se pudieron sincronizar los submodulos automaticamente.
    echo        Ejecuta luego: git submodule update --init --recursive
)

:after_submodules
echo.
echo [5/6] Verificando 7-Zip para Windows...
if exist "C:\Program Files\7-Zip\7z.exe" if exist "C:\Program Files\7-Zip\7z.sfx" goto sevenzip_ok
if exist "C:\Program Files (x86)\7-Zip\7z.exe" if exist "C:\Program Files (x86)\7-Zip\7z.sfx" goto sevenzip_ok

where winget >nul 2>&1
if errorlevel 1 (
    echo [WARN] winget no esta disponible.
    echo        El build de desarrollo funcionara.
    echo        Para generar JW-QET-Portable.exe instala 7-Zip para Windows.
    goto verify
)

echo [INFO] Instalando 7-Zip para Windows con winget...
winget install --id 7zip.7zip -e --silent --accept-package-agreements --accept-source-agreements
if errorlevel 1 (
    echo [WARN] winget no pudo instalar 7-Zip.
    echo        El build de desarrollo funcionara, pero el SFX portable puede fallar.
    goto verify
)

:sevenzip_ok
echo [OK] 7-Zip para Windows disponible.

:verify
echo.
echo Verificando herramientas clave...
set "FAILED=0"

if exist "%MSYS_ROOT%\ucrt64\bin\cmake.exe" (echo [OK] cmake.exe) else (echo [FALTA] cmake.exe & set "FAILED=1")
if exist "%MSYS_ROOT%\ucrt64\bin\ninja.exe" (echo [OK] ninja.exe) else (echo [FALTA] ninja.exe & set "FAILED=1")
if exist "%MSYS_ROOT%\ucrt64\bin\g++.exe" (echo [OK] g++.exe) else (echo [FALTA] g++.exe & set "FAILED=1")
if exist "%MSYS_ROOT%\ucrt64\bin\windeployqt-qt5.exe" (echo [OK] windeployqt-qt5.exe) else (echo [FALTA] windeployqt-qt5.exe & set "FAILED=1")
if exist "%MSYS_ROOT%\ucrt64\bin\objdump.exe" (echo [OK] objdump.exe) else (echo [FALTA] objdump.exe & set "FAILED=1")
if exist "%MSYS_ROOT%\ucrt64\bin\Qt5Svg.dll" (echo [OK] Qt5Svg.dll) else (echo [FALTA] Qt5Svg.dll & set "FAILED=1")

if "%FAILED%"=="1" (
    echo.
    echo [ERROR] El entorno quedo incompleto.
    pause
    exit /b 1
)

echo.
echo [6/6] Generando JW-QET-Launcher.exe...
call "%REPO%build-jw-qet-launcher.bat"
if errorlevel 1 (
    echo.
    echo [ERROR] El entorno esta instalado, pero no se pudo generar el launcher.
    echo        Puedes reintentar con: build-jw-qet-launcher.bat
    pause
    exit /b 1
)

if exist "%INSTALLER%" del /Q "%INSTALLER%" >nul 2>&1

echo.
echo ============================================================
echo   SETUP COMPLETADO
echo ============================================================
echo.
echo Para uso normal, sin consola:
echo   JW-QET-Launcher.exe
echo.
echo Para depurar y ver la consola:
echo   run-jw-qet-dev.bat --wait
echo.
echo Para generar release:
echo   build-jw-qet.bat
echo.
pause
exit /b 0
