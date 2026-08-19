# JW QET MVP Workflow

Fecha: 2026-08-19

Este documento define el flujo operativo minimo para validar colaboracion por folio en el fork interno de JW Control.

## Decision

Para el MVP inmediato usaremos una carpeta compartida tipo Google Drive como transporte de archivos, con merge controlado por herramienta.

GitHub se mantiene como:

- repositorio del codigo del fork;
- historial tecnico de la herramienta;
- posible respaldo/versionado posterior de proyectos aprobados.

No usaremos GitHub como mecanismo principal para que dos proyectistas editen proyectos QET en esta primera validacion, porque obligaria a introducir commits, ramas, pulls y posibles conflictos Git en el flujo diario. Para una prueba en menos de una hora, Google Drive con copias locales controladas reduce friccion.

## Regla principal

Nadie edita directamente el archivo maestro compartido al mismo tiempo.

QElectroTech guarda el proyecto completo. Si dos PCs guardan sobre el mismo `.qet`, la ultima sincronizacion de Drive puede sobrescribir cambios o crear copias en conflicto.

El MVP evita eso con este contrato:

- el maestro compartido es solo punto de partida y punto de publicacion;
- cada usuario edita una copia local;
- cada usuario trabaja en folios asignados;
- la publicacion se hace fusionando copias contra el maestro/base con `tools/qet_collab_session.py` y `tools/qet_folio_merge.py`;
- si dos copias modifican el mismo folio, el merge se rechaza.
- el mapeo maestro/baseline/copia local/entrega vive en un manifiesto sidecar `.jwqet.json`, no dentro del `.qet`.

## Estructura recomendada

Raiz compartida en Drive, nombre sugerido:

```text
JW_QET_COLLAB/
  00_SETUP/
    JW_QET_Portable_Setup.exe
    JW_QET_Portable.7z
  00_MASTER/
    Proyecto.qet
  01_BASELINES/
    2026-08-19_1300_Proyecto.qet
  02_WORKING/
    usuario_1/
    usuario_2/
  03_INCOMING/
    usuario_1/
    usuario_2/
  04_PUBLISHED/
  05_ARCHIVE/
  06_LOGS/
```

Uso de carpetas:

- `00_SETUP`: instalador/paquete portable del fork para PCs que no compilan QET localmente.
- `00_MASTER`: ultimo proyecto aprobado.
- `01_BASELINES`: copia congelada desde la cual parten las ediciones de una ronda.
- `02_WORKING`: copias locales o sincronizadas en las que cada usuario trabaja.
- `03_INCOMING`: copias que los usuarios entregan para fusionar.
- `04_PUBLISHED`: salidas generadas por la herramienta antes de promoverlas a maestro.
- `05_ARCHIVE`: maestros anteriores y copias usadas en rondas cerradas.
- `06_LOGS`: salidas de `analyze`/`merge` y notas de decision.

## Roles del MVP

- Integrador: persona que ejecuta `analyze` y `merge`, revisa advertencias y publica el nuevo maestro.
- Usuario editor: persona que abre su copia, edita solo folios asignados y entrega su `.qet`.

Durante el MVP podemos operar con un solo integrador. Mas adelante esto puede convertirse en una herramienta con interfaz.

## Mapeo colaborativo

La idea de UI en QET se modela primero con un manifiesto:

```text
Proyecto_usuario_20260819_130000.qet
Proyecto_usuario_20260819_130000.qet.jwqet.json
```

El manifiesto guarda:

- ruta del maestro;
- ruta de la baseline congelada;
- ruta de la copia local de trabajo;
- ruta de entrega en `03_INCOMING`;
- carpeta de publicacion en `04_PUBLISHED`;
- usuario;
- hashes SHA-256 del maestro/baseline/copia.

Esto evita cambiar el formato `.qet`. QET ya crea y consume este manifiesto desde la opcion `Archivo > Crear copia de trabajo colaborativa...`.

## Flujo desde QET

El fork ya incluye un primer puente grafico en el menu `Archivo`:

- `Crear copia de trabajo colaborativa...`
- `Entregar cambios colaborativos...`

`Crear copia de trabajo colaborativa...` pide:

- archivo maestro `.qet`, normalmente `00_MASTER\Proyecto.qet`;
- carpeta colaborativa raiz, normalmente `JW_QET_COLLAB`;
- nombre del usuario/editor.

Luego crea baseline, copia de trabajo y manifiesto sidecar `.jwqet.json`, y abre la copia de trabajo en QET. Este paso se ejecuta directamente dentro de QET; no requiere PowerShell ni Python en la PC del usuario.

`Entregar cambios colaborativos...` funciona sobre el proyecto activo. Primero guarda la copia local `.qet`, busca el manifiesto sidecar junto al archivo abierto y prepara la entrega en `03_INCOMING\<usuario>\`. Este paso tambien se ejecuta directamente dentro de QET.

Para una segunda PC que no tenga compilado el repo, usar el paquete:

```text
JW_QET_COLLAB\00_SETUP\JW_QET_Portable_Setup.exe
```

Ejecutarlo con doble clic. El instalador autoextraible despliega QET en una ruta corta bajo `%LOCALAPPDATA%\JWControl\JW_QET_Portable` y abre QElectroTech. Ese flujo evita el limite de rutas largas del extractor de Windows.

Como alternativa tecnica, `JW_QET_Portable.7z` se puede extraer manualmente con 7-Zip en una ruta corta como `C:\JW_QET`. No extraer el paquete con Explorer en Escritorio/Documentos si Windows reporta `Ruta de acceso demasiado larga`.

La publicacion/fusion de varias entregas todavia queda fuera de QET en esta iteracion y se ejecuta con `tools/qet_collab_session.py merge`. Ese limite es intencional: el objetivo de este paso es validar apertura y entrega desde QET sin cambiar el formato `.qet` ni introducir locks/servidor.

## Flujo de una ronda

1. Cada usuario usa `Archivo > Crear copia de trabajo colaborativa...` indicando maestro, workspace y nombre de usuario.
2. QET crea una baseline congelada, una copia local y un manifiesto `.jwqet.json`, y abre la copia local.
3. Como alternativa tecnica, el integrador puede ejecutar `checkout` por PowerShell.
4. Cada usuario edita solamente los folios asignados.
5. Cada usuario usa `Archivo > Entregar cambios colaborativos...` para guardar y colocar la entrega en `03_INCOMING/<usuario>/`.
6. El integrador ejecuta `merge` usando los manifiestos de entrega.
7. La herramienta rechaza automaticamente el merge si dos entregas modifican el mismo folio de forma distinta.
8. El integrador abre el resultado desde el build del fork y hace revision visual.
9. El integrador guarda una copia desde QET para confirmar que el guardado oficial la acepta.
10. Si la validacion pasa, el integrador promueve el resultado a `00_MASTER/Proyecto.qet` y archiva el maestro anterior.

## Comandos base

Generar paquete portable e instalador autoextraible desde el repo:

```bat
build-jw-qet-portable-exe.bat
```

Crear copia de trabajo:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_collab_session.py checkout `
  --master <00_MASTER\Proyecto.qet> `
  --workspace <JW_QET_COLLAB> `
  --user <usuario>
```

Entregar cambios:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_collab_session.py submit `
  --manifest <copia_local.qet.jwqet.json>
```

Fusionar entregas desde manifiestos:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_collab_session.py merge `
  --output <04_PUBLISHED\Proyecto_publicado.qet> `
  <usuario_1_entrega.qet.jwqet.json> `
  <usuario_2_entrega.qet.jwqet.json>
```

Diagnostico interno con la herramienta base:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_folio_merge.py analyze `
  <baseline.qet> `
  <usuario_1.qet> `
  <usuario_2.qet>
```

Merge interno sin manifiestos:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_folio_merge.py merge `
  --base <baseline.qet> `
  --output <published.qet> `
  <usuario_1.qet> `
  <usuario_2.qet>
```

Si la salida ya existe y se quiere regenerar el mismo artefacto de prueba:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_collab_session.py merge `
  --output <published.qet> `
  --force `
  <usuario_1_entrega.qet.jwqet.json> `
  <usuario_2_entrega.qet.jwqet.json>
```

## Criterio de aceptacion MVP

Una ronda es aceptada si:

- `merge` termina en `Estado del merge: OK`;
- todos los manifiestos parten de la misma baseline;
- los folios modificados reportados coinciden con los folios asignados;
- no hay conflicto por el mismo folio;
- QET abre el `.qet` publicado desde el build del fork;
- QET puede guardarlo de nuevo;
- los elementos y conductores esperados siguen visibles;
- los conductores reportados por `analyze` aparecen como `ok`;
- `/project/collection` contiene los elementos embebidos requeridos.

## Que hacer ante conflictos

Si `merge` reporta conflicto:

- no se publica un nuevo maestro;
- el integrador identifica el folio en conflicto;
- los usuarios deciden manualmente cual copia conservar o rehacen la edicion desde la baseline vigente;
- no se intenta resolver automaticamente en esta iteracion.

## Limites intencionales

Este MVP no incluye:

- edicion simultanea del mismo folio;
- locks automaticos;
- servidor;
- WebSocket;
- base de datos;
- autenticacion;
- cambios al formato `.qet`;
- merge automatico de referencias cruzadas, borneras o autonumeracion global.

## Riesgos conocidos

- QET guarda el proyecto completo, asi que el archivo maestro debe tratarse como recurso publicado, no como archivo de trabajo compartido.
- Google Drive puede crear copias en conflicto si dos personas escriben el mismo archivo.
- QET puede reordenar nodos XML y ampliar `/project/collection` al guardar.
- El identificador de folio persistente aun no esta resuelto; por ahora la herramienta identifica folios por `order`.
- Cambios globales como propiedades de proyecto, autonumeraciones, borneras y referencias cruzadas pueden requerir reglas adicionales.

## Proxima hora

Para convertir esto en MVP validado:

1. Probar textos/propiedades de folio.
2. Probar referencias cruzadas, autonumeracion y borneras.
3. Promover el flujo a una carpeta real de Google Drive compartida.
4. Agregar una forma comoda de abrir la copia local generada desde el launcher del fork.

## Validacion local del MVP

Validado el 2026-08-19 en:

```text
C:\Users\jeykc\Documentos\GitHub\qelectrotech-source-mirror\build\qet-collab-mvp
```

Ronda exitosa:

- Workspace: `JW_QET_COLLAB`.
- Maestro: `00_MASTER\Proyecto.qet`, copiado desde `Conexion_Base.qet`.
- `checkout` genero copias para `usuario_1` y `usuario_2`.
- Se simulo que `usuario_1` edito el folio `order:1` usando `Conexion_01.qet`.
- Se simulo que `usuario_2` edito el folio `order:2` usando `Conexion_02.qet`.
- `submit` envio ambas copias a `03_INCOMING`.
- `merge` publico `04_PUBLISHED\Proyecto_Publicado.qet`.
- Resultado: `Estado del merge: OK`.
- El archivo publicado conserva 2 folios, 4 conductores validos en el folio 1, 2 conductores validos en el folio 2 y los elementos embebidos requeridos.

Ronda conflictiva:

- Workspace: `JW_QET_CONFLICT`.
- Ambos usuarios partieron de la misma baseline.
- Se simulo que ambos modificaron el folio `order:1` de forma distinta.
- `merge` devolvio `Estado del merge: CONFLICTO`.
- No se genero `04_PUBLISHED\Proyecto_Conflictivo.qet`.
- Resultado esperado: el MVP bloquea la publicacion si dos usuarios modifican el mismo folio con contenido distinto.

## Workspace real en Google Drive

Configurado el 2026-08-19 en:

```text
H:\Mi unidad\01_JW_CONTROL\04_PRODUCTOS\03_ACTIVOS\JWPLC_LAUNDRY\03_IMPLEMENTACIONES_CLIENTE\2026-008_KOKETA\02_DIAGRAMA_ELECTRICO\JW_QET_COLLAB
```

Estado inicial:

- Se creo la estructura `00_MASTER`, `01_BASELINES`, `02_WORKING`, `03_INCOMING`, `04_PUBLISHED`, `05_ARCHIVE` y `06_LOGS`.
- Se copio como maestro inicial `00_MASTER\Proyecto.qet`.
- El maestro fue analizado correctamente desde la ruta `H:`:
  - 2 folios;
  - 6 conductores validos;
  - elementos embebidos requeridos presentes.

Copia de trabajo creada:

```text
02_WORKING\jeykc\Proyecto_jeykc_20260819_133800.qet
```

Manifiesto de esa copia:

```text
02_WORKING\jeykc\Proyecto_jeykc_20260819_133800.qet.jwqet.json
```

Regla para la siguiente validacion:

- Abrir y editar la copia de trabajo, no `00_MASTER\Proyecto.qet`.
- Al terminar, ejecutar `submit` con el manifiesto de la copia.
- El archivo entregado aparecera en `03_INCOMING\jeykc`.
