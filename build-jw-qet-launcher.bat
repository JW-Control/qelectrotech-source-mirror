@echo off
setlocal EnableExtensions

set "REPO=%~dp0"
if "%REPO:~-1%"=="\" set "REPO=%REPO:~0,-1%"

set "UCRT_BIN=C:\msys64\ucrt64\bin"
set "CXX=%UCRT_BIN%\g++.exe"
set "OBJDUMP=%UCRT_BIN%\objdump.exe"
set "SRC=%REPO%\packaging\windows\jw-qet-launcher.cpp"
set "OUT=%REPO%\JW-QET-Launcher.exe"
set "IMPORTS=%TEMP%\jw-qet-launcher-imports-%RANDOM%.txt"
set "PATH=%UCRT_BIN%;%PATH%"

if not exist "%CXX%" (
    echo [ERROR] No se encontro el compilador UCRT64:
    echo         %CXX%
    echo.
    echo Ejecuta primero:
    echo   setup-jw-qet-dev-environment.bat
    exit /b 1
)

if not exist "%OBJDUMP%" (
    echo [ERROR] No se encontro objdump UCRT64:
    echo         %OBJDUMP%
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
echo [INFO] Compilando launcher Win32 autocontenido y sin consola...
"%CXX%" ^
  -std=c++17 ^
  -O2 ^
  -s ^
  -Wall ^
  -Wextra ^
  -municode ^
  -mwindows ^
  -static ^
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
    echo [INFO] Compilando launcher Win32 autocontenido y sin consola... hasta esta linea.
    exit /b %RC%
)

if not exist "%OUT%" (
    echo [ERROR] El compilador termino sin generar:
    echo         %OUT%
    exit /b 1
)

echo.
echo [INFO] Verificando dependencias runtime del launcher...
"%OBJDUMP%" -p "%OUT%" > "%IMPORTS%"
if errorlevel 1 (
    echo [ERROR] No se pudieron inspeccionar las dependencias del launcher.
    if exist "%IMPORTS%" del /Q "%IMPORTS%" >nul 2>&1
    exit /b 1
)

findstr /I /C:"libwinpthread-1.dll" /C:"libgcc_s_seh-1.dll" /C:"libstdc++-6.dll" "%IMPORTS%" >nul 2>&1
if not errorlevel 1 (
    echo.
    echo [ERROR] El launcher aun depende de una DLL runtime de MinGW.
    echo         Esto no es valido para el launcher autocontenido.
    echo.
    findstr /I /C:"DLL Name:" "%IMPORTS%"
    del /Q "%IMPORTS%" >nul 2>&1
    del /Q "%OUT%" >nul 2>&1
    exit /b 1
)

echo [OK] Sin dependencias dinamicas de libwinpthread/libgcc/libstdc++.
del /Q "%IMPORTS%" >nul 2>&1

echo.
echo [OK] Launcher listo:
echo      %OUT%
exit /b 0
