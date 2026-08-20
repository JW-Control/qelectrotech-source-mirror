@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"

set "UCRT_BIN=C:\msys64\ucrt64\bin"
set "CXX=%UCRT_BIN%\g++.exe"
set "SRC=%REPO%\packaging\windows\jw-qet-launcher.cpp"
set "OUT=%REPO%\JW-QET-Launcher.exe"
set "PATH=%UCRT_BIN%;%PATH%"

if not exist "%CXX%" (
    echo [ERROR] No se encontro el compilador UCRT64:
    echo         %CXX%
    echo.
    echo Ejecuta primero:
    echo   setup-jw-qet-dev-environment.bat
    exit /b 1
)

if not exist "%SRC%" (
    echo [ERROR] No se encontro el codigo fuente del launcher:
    echo         %SRC%
    exit /b 1
)

echo ============================================================
echo   JW QET - Build del launcher grafico
echo ============================================================
echo Fuente : %SRC%
echo Salida : %OUT%
echo.
echo [INFO] Compilador:
"%CXX%" --version
if errorlevel 1 (
    echo.
    echo [ERROR] g++.exe existe pero no puede inicializarse correctamente.
    echo         Verifica las DLL de MSYS2 UCRT64 en:
    echo         %UCRT_BIN%
    exit /b 1
)

echo.
echo [INFO] Compilando launcher Win32 sin consola...
"%CXX%" ^
  -std=c++17 ^
  -O2 ^
  -s ^
  -Wall ^
  -Wextra ^
  -municode ^
  -mwindows ^
  -static-libgcc ^
  -static-libstdc++ ^
  "%SRC%" ^
  -o "%OUT%" ^
  -luser32 ^
  -lkernel32 ^
  -lgdi32

set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" (
    echo.
    echo [ERROR] Fallo la compilacion de JW-QET-Launcher.exe.
    echo         Codigo de salida de g++: %RC%
    echo.
    echo Si arriba aparece un error de compilador o linker, copia desde
    echo [INFO] Compilando launcher Win32 sin consola... hasta esta linea.
    exit /b %RC%
)

if not exist "%OUT%" (
    echo [ERROR] El compilador termino sin generar:
    echo         %OUT%
    exit /b 1
)

echo.
echo [OK] Launcher listo:
echo      %OUT%
exit /b 0
