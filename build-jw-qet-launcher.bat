@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"

set "CXX=C:\msys64\ucrt64\bin\g++.exe"
set "SRC=%REPO%\packaging\windows\jw-qet-launcher.cpp"
set "OUT=%REPO%\JW-QET-Launcher.exe"

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

if errorlevel 1 (
    echo.
    echo [ERROR] Fallo la compilacion de JW-QET-Launcher.exe.
    exit /b 1
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
