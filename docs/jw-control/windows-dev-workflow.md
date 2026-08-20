# JW QET - Flujo de desarrollo y distribucion en Windows

Este documento describe el flujo interno de JW Control para compilar, ejecutar y empaquetar el fork de QElectroTech en Windows con Qt5 sobre MSYS2 UCRT64.

## Primera instalacion en una PC

Clone el repositorio incluyendo submodulos:

```bat
git clone --recurse-submodules https://github.com/JW-Control/qelectrotech-source-mirror.git
cd qelectrotech-source-mirror
```

Si el repositorio ya fue clonado sin submodulos:

```bat
git submodule update --init --recursive
```

Luego ejecute:

```bat
setup-jw-qet-dev-environment.bat
```

El script solicita elevacion UAC cuando la necesita. Instala o actualiza MSYS2 en `C:\msys64`, instala el toolchain UCRT64/Qt5 usado por el workflow Windows del fork y procura instalar 7-Zip para construir el ejecutable portable autoextraible.

## Desarrollo rapido

El comando recomendado durante desarrollo es:

```bat
run-jw-qet-dev.bat
```

Este flujo configura `build\jw-qet-dev` la primera vez, recompila incrementalmente los cambios de C/C++ y ejecuta `qelectrotech.exe` directamente usando `elements`, `titleblocks` y `lang` desde el estado actual del repositorio. No genera ningun release.

Opciones utiles:

```bat
run-jw-qet-dev.bat --no-build
run-jw-qet-dev.bat --clean
run-jw-qet-dev.bat --qt-debug
```

- `--no-build`: ejecuta el ultimo binario sin recompilar.
- `--clean`: elimina `build\jw-qet-dev`, reconfigura, recompila y ejecuta.
- `--qt-debug`: activa `QT_DEBUG_PLUGINS=1` para diagnosticar plugins Qt.

El tipo de build de desarrollo por defecto es `RelWithDebInfo`. Para usar simbolos Debug completos:

```bat
set JW_QET_BUILD_TYPE=Debug
run-jw-qet-dev.bat --clean
```

## Compilar sin ejecutar

```bat
build-jw-qet-dev.bat
```

Build limpio:

```bat
build-jw-qet-dev.bat --clean
```

## Release completo

```bat
build-jw-qet.bat
```

Build CMake:

```text
build\jw-qet-qt5-nokf
```

Staging temporal:

```text
build\p\JW_QET_Portable
```

Artefactos finales:

```text
release\
  JW-QET-Portable.exe
  JW-QET-Portable.7z
  SHA256SUMS.txt
```

`build\` y `release\` deben quedar fuera de Git.

Build Release desde cero:

```bat
build-jw-qet.bat --clean
```

## Reempaquetar sin recompilar

Si `build\jw-qet-qt5-nokf\qelectrotech.exe` ya existe:

```bat
package-jw-qet.bat
```

Conservar staging para inspeccion:

```bat
package-jw-qet.bat -KeepStage
```

Solo archivo `.7z`:

```bat
package-jw-qet.bat -NoSfx
```

`build-jw-qet-portable-exe.bat` se mantiene como alias de compatibilidad y llama a `package-jw-qet.bat`.

## Por que el desarrollo no usa el portable

El flujo de desarrollo ejecuta el binario directamente contra los recursos del repositorio. Esto evita copiar miles de archivos en cada prueba.

El flujo de release crea un staging autocontenido, ejecuta `windeployqt`, resuelve DLL con `objdump`, empaqueta el arbol completo y publica solo los artefactos de `release\`.

El staging no debe mezclarse con la raiz del repositorio porque contiene copias de `elements`, `titleblocks`, `lang`, `fonts`, plugins y DLL de Qt.

## Instalacion del portable

`JW-QET-Portable.exe` extrae o actualiza la aplicacion en:

```text
%LOCALAPPDATA%\JWControl\JW_QET_Portable
```

y luego ejecuta `run-qelectrotech.bat`.

`SHA256SUMS.txt` permite comprobar la integridad de los artefactos al copiarlos a otra PC.
