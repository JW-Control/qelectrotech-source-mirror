# QET Source Map - colaboración por folio

Fecha de revisión: 2026-08-19

Este documento es el mapa inicial del código fuente para el fork privado de JW Control. Resume lo confirmado en el repositorio antes de modificar funcionalidad. El objetivo inmediato es entender QElectroTech original, su arquitectura de proyectos/folios, el formato `.qet`, Undo/Redo e identificadores persistentes.

No cubre todavía CRDT, servidor, WebSocket, base de datos colaborativa, autenticación ni edición simultánea.

## Estado del repositorio

Confirmado localmente:

- Rama actual: `master`.
- HEAD: `5f8367975` (`Update paths_compilation_installation.cmake`).
- Tags en HEAD: ninguno.
- Versión declarada por CMake: `0.100.1` en `CMakeLists.txt`.
- README: rama de desarrollo `0.100.1`; estable `0.100`, publicada el `2026-01-25`.
- Remotes:
  - `origin`: `https://github.com/JW-Control/qelectrotech-source-mirror.git`
  - `upstream`: `https://github.com/qelectrotech/qelectrotech-source-mirror.git`
- Estado de trabajo al inicio de la revisión: limpio.

Submódulos declarados en `.gitmodules`:

- `pugixml`
- `SingleApplication`
- `elements`
- `doxygen-awesome-css`

Nota local: `git submodule status` falló por herramientas auxiliares rotas o ausentes en Git-for-Windows (`basename`, `sed`, `git-sh-setup`). Las carpetas existen y cada submódulo responde a `git -C <submodule> rev-parse --is-inside-work-tree`.

## Estructura relevante

Raíz del repositorio:

- `CMakeLists.txt`: configuración principal de CMake.
- `qelectrotech.pro`: proyecto qmake todavía presente.
- `.github/workflows/windows-build.yml`: referencia práctica para compilar en Windows/MSYS2.
- `sources/`: código principal de la aplicación.
- `sources/qetproject.*`: modelo de proyecto `.qet`.
- `sources/diagram.*`: escena de un folio.
- `sources/diagramview.*`: vista gráfica de un folio.
- `sources/projectview.*`: UI de proyecto, pestañas de folios, guardar/cerrar/reordenar.
- `sources/qetdiagrameditor.*`: ventana principal del editor de esquemas.
- `sources/qetgraphicsitem/`: elementos gráficos del folio (`Element`, `Conductor`, `Terminal`, textos, imágenes, etc.).
- `sources/undocommand/`: comandos Undo/Redo principales del editor de folios/proyecto.
- `sources/diagramevent/`: acciones interactivas que terminan empujando comandos al `QUndoStack`.
- `sources/ElementsCollection/`: colección de elementos, incluyendo colección embebida dentro del proyecto.
- `sources/TerminalStrip/`: lógica de borneras/terminal strips.
- `sources/properties/`: estructuras serializables de propiedades.
- `sources/xml/`: helpers XML para partes específicas.
- `elements/`: biblioteca de símbolos como submódulo.
- `tests/`: pruebas del proyecto.

## Sistema de compilación

Confirmado:

- Sistema principal: CMake.
- Sistema alternativo/heredado: qmake (`qelectrotech.pro`).
- CMake mínimo: `3.5...4.2`.
- Lenguaje: C++17.
- Qt por defecto: Qt 5, salvo `-DQT_VERSION_MAJOR=6`.
- Componentes Qt declarados en `cmake/qet_compilation_vars.cmake`:
  - `LinguistTools`
  - `PrintSupport`
  - `Xml`
  - `Svg`
  - `Sql`
  - `Network`
  - `Widgets`
  - `Concurrent`
- También se enlaza `Qt::GuiPrivate`.
- `SQLite3` es requerido por CMake.
- KDE Frameworks está habilitado por defecto con `BUILD_WITH_KF=ON`:
  - `KFCoreAddons`
  - `KFWidgetsAddons`
- Las pruebas se habilitan por defecto con `PACKAGE_TESTS=ON`.

Estado de esta PC:

- Existe MSYS2 en `C:\msys64`.
- En `C:\msys64\ucrt64\bin` se encontraron:
  - `cmake.exe` 4.3.3
  - `g++.exe` 16.1.0
  - `ninja.exe` 1.13.2
- No se encontró Qt5/Qt6 en `C:\msys64\ucrt64`.
- No se encontró `C:\Qt`.
- `pacman -Q` mostró instalados `cmake`, `gcc`, `ninja`, `pkgconf`; no mostró instalados Qt5/KF/SQLite.
- `pacman` reportó errores de firma/keyring en las bases de datos de MSYS2. Antes de instalar dependencias probablemente hay que reparar/actualizar MSYS2.

Ruta de compilación recomendada en esta PC, basada en el workflow Windows:

1. Usar MSYS2 UCRT64.
2. Instalar/reparar dependencias:
   - `mingw-w64-ucrt-x86_64-qt5-base`
   - `mingw-w64-ucrt-x86_64-qt5-svg`
   - `mingw-w64-ucrt-x86_64-qt5-tools`
   - `mingw-w64-ucrt-x86_64-qt5-translations`
   - `mingw-w64-ucrt-x86_64-qt5-pdf`
   - `mingw-w64-ucrt-x86_64-sqlite3`
   - `mingw-w64-ucrt-x86_64-kwidgetsaddons`
   - `mingw-w64-ucrt-x86_64-kcoreaddons`
   - `mingw-w64-ucrt-x86_64-extra-cmake-modules`
   - `mingw-w64-ucrt-x86_64-pkgconf`
   - `mingw-w64-ucrt-x86_64-ninja`
   - `mingw-w64-ucrt-x86_64-gcc`
3. Configurar en un directorio de build separado:

```bash
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH=/ucrt64 \
  -DQt5_DIR=/ucrt64/lib/cmake/Qt5 \
  -DQT_VERSION_MAJOR=5 \
  -DCMAKE_DISABLE_FIND_PACKAGE_Qt6=ON \
  -DPACKAGE_TESTS=OFF \
  -DCMAKE_POLICY_DEFAULT_CMP0077=NEW \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DQET_EXPORT_PROJECT_DB=ON \
  -DSQLite3_INCLUDE_DIR=/ucrt64/include \
  -DSQLite3_LIBRARY=/ucrt64/lib/libsqlite3.dll.a \
  ..
ninja
```

Pendiente: compilar QElectroTech original en esta PC después de instalar/reparar dependencias.

## Resultado de compilación local

Confirmado el `2026-08-19`:

- Se actualizó `msys2-keyring`.
- Se instalaron dependencias Qt5/MSYS2 UCRT64 necesarias para compilar.
- Se ejecutó una actualización completa de MSYS2 porque `cmake.exe` buscaba `libjsoncpp-27.dll` pero el sistema tenía `libjsoncpp-26.dll`.
- Después de la actualización, `cmake --version` respondió correctamente con `4.4.2`.
- La configuración CMake fue exitosa en `build/jw-qet-qt5-nokf`.
- La compilación con Ninja terminó correctamente y generó `build/jw-qet-qt5-nokf/qelectrotech.exe`.
- La prueba no interactiva `qelectrotech.exe --version` respondió `0.200.1-dev`.

Configuración usada:

```bash
cmake -S . -B build/jw-qet-qt5-nokf -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_MAKE_PROGRAM=/ucrt64/bin/ninja.exe \
  -DCMAKE_C_COMPILER=/ucrt64/bin/gcc.exe \
  -DCMAKE_CXX_COMPILER=/ucrt64/bin/g++.exe \
  -DCMAKE_PREFIX_PATH=/ucrt64 \
  -DQt5_DIR=/ucrt64/lib/cmake/Qt5 \
  -DQT_VERSION_MAJOR=5 \
  -DCMAKE_DISABLE_FIND_PACKAGE_Qt6=ON \
  -DCMAKE_DISABLE_FIND_PACKAGE_Git=ON \
  -DFETCHCONTENT_SOURCE_DIR_PUGIXML=C:/Users/jeykc/Documentos/GitHub/qelectrotech-source-mirror/pugixml \
  -DFETCHCONTENT_SOURCE_DIR_SINGLEAPPLICATION=C:/Users/jeykc/Documentos/GitHub/qelectrotech-source-mirror/SingleApplication \
  -DPACKAGE_TESTS=OFF \
  -DBUILD_WITH_KF=OFF \
  -DCMAKE_POLICY_DEFAULT_CMP0077=NEW \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DQET_EXPORT_PROJECT_DB=ON \
  -DSQLite3_INCLUDE_DIR=/ucrt64/include \
  -DSQLite3_LIBRARY=/ucrt64/lib/libsqlite3.dll.a
```

Compilación:

```bash
ninja -C build/jw-qet-qt5-nokf
```

Notas:

- `BUILD_WITH_KF=OFF` usa las alternativas `sources/ui/nokde/*`. Fue necesario para esta primera compilación Qt5 porque MSYS2 UCRT64 instaló KDE Frameworks 6, no KF5.
- `CMAKE_DISABLE_FIND_PACKAGE_Git=ON` fue necesario en esta sesión porque CMake intentó ejecutar `git submodule update --init --recursive` y escribir en `.git/modules/...`, ruta bloqueada por el sandbox. Como los submódulos ya estaban presentes, se pasaron rutas locales de `pugixml` y `SingleApplication`.
- CMake declara `PROJECT_VERSION 0.100.1`, pero la versión runtime sale de `sources/qetversion.cpp` y actualmente es `0.200.1-dev`.
- La generación de traducciones modificó archivos binarios `.qm` en `lang/`. Esos cambios son artefactos de build y no deben mezclarse con cambios funcionales.
- Al abrir `qelectrotech.exe` directamente desde Explorer aparecieron errores por DLLs ausentes (`Qt5Concurrent.dll`, `Qt5Core.dll`, `libstdc++-6.dll`, `libgcc_s_seh-1.dll`). La causa no era un fallo de compilación, sino que el ejecutable depende de DLLs de MSYS2 UCRT64 que no están en el `PATH` de Explorer.
- Se ejecutó `windeployqt-qt5.exe --release --compiler-runtime --no-angle --force build/jw-qet-qt5-nokf/qelectrotech.exe` para copiar DLLs Qt, plugins y runtime MinGW al directorio del build.
- Se copió manualmente `libsqlite3-0.dll` al directorio del build porque QET enlaza SQLite directamente.
- Se creó `build/jw-qet-qt5-nokf/run-qelectrotech.bat` como launcher local. El launcher agrega el directorio del build y `C:\msys64\ucrt64\bin` al `PATH`, arranca con working directory en la raíz del repo y pasa rutas explícitas para `elements`, `titleblocks` y `lang`.

## Primeros archivos a inspeccionar

Para trabajo incremental, estos son los archivos iniciales confirmados:

- `CMakeLists.txt`
- `cmake/qet_compilation_vars.cmake`
- `cmake/developer_options.cmake`
- `.github/workflows/windows-build.yml`
- `sources/qetdiagrameditor.h`
- `sources/qetdiagrameditor.cpp`
- `sources/projectview.h`
- `sources/projectview.cpp`
- `sources/qetproject.h`
- `sources/qetproject.cpp`
- `sources/diagram.h`
- `sources/diagram.cpp`
- `sources/diagramview.h`
- `sources/diagramview.cpp`
- `sources/qetgraphicsitem/element.h`
- `sources/qetgraphicsitem/element.cpp`
- `sources/qetgraphicsitem/conductor.h`
- `sources/qetgraphicsitem/conductor.cpp`
- `sources/qetgraphicsitem/terminal.h`
- `sources/qetgraphicsitem/terminal.cpp`
- `sources/properties/terminaldata.h`
- `sources/properties/terminaldata.cpp`
- `sources/undocommand/*`
- `sources/diagramevent/*`

Nota: no se encontró una clase `DiagramScene`. En el editor de proyectos, `Diagram` hereda directamente de `QGraphicsScene`. Existe `ElementScene` en `sources/editor/elementscene.*`, pero corresponde al editor de símbolos/elementos, no al folio de proyecto.

## Clases principales

### `QETProject`

- Header: `sources/qetproject.h`
- Implementación: `sources/qetproject.cpp`
- Responsabilidad: representa un proyecto QElectroTech completo, guardado como `.qet`. Agrupa folios (`Diagram`), propiedades del proyecto, colección embebida de elementos, plantillas de cartucho embebidas, autonumeraciones y borneras.
- Relaciones:
  - Posee `QList<Diagram *> m_diagrams_list`.
  - Posee un `QUndoStack` del proyecto.
  - Lee/escribe XML de proyecto completo.
  - Usa `XmlElementCollection` para elementos embebidos.
  - Mantiene datos de folio mediante `updateDiagramsFolioData()`.
- Puntos importantes para colaboración:
  - Es la frontera natural del archivo `.qet`.
  - El `QUndoStack` es por proyecto, no por folio.
  - El guardado actual escribe todo el proyecto.
  - Existe `QUuid m_uuid`, pero no se observó serialización de ese UUID en el XML del proyecto.

### `Diagram`

- Header: `sources/diagram.h`
- Implementación: `sources/diagram.cpp`
- Responsabilidad: representa un folio/esquema eléctrico. Hereda de `QGraphicsScene`.
- Relaciones:
  - Pertenece a un `QETProject`.
  - Contiene items gráficos: `Element`, `Conductor`, textos independientes, imágenes, formas, tablas y terminal strip items.
  - Serializa y deserializa el contenido de un folio.
  - Devuelve el `QUndoStack` del proyecto mediante `Diagram::undoStack()`.
- Puntos importantes para colaboración:
  - `Diagram::toXml()` permite serializar un folio individual.
  - `Diagram::fromXml()` puede reconstruir un folio desde un elemento `<diagram>`.
  - Existe `QUuid m_uuid` en memoria, pero no se observó que `Diagram::toXml()` escriba un atributo `uuid` para el folio.
  - El atributo `order` de `<diagram>` lo agrega `QETProject::toXml()`, no `Diagram::toXml()`.

### `DiagramView`

- Header: `sources/diagramview.h`
- Implementación: `sources/diagramview.cpp`
- Responsabilidad: vista gráfica de un `Diagram`. Hereda de `QGraphicsView`.
- Relaciones:
  - Envuelve un `Diagram`.
  - Participa en interacción de usuario, visualización, zoom, selección, copiar/pegar y drag/drop.
- Puntos importantes para colaboración:
  - Es una capa de UI, no el modelo persistente.
  - Podría servir para mostrar estado futuro de bloqueo/lectura por folio, pero no debería ser el origen de verdad.

### `ProjectView`

- Header: `sources/projectview.h`
- Implementación: `sources/projectview.cpp`
- Responsabilidad: widget de proyecto. Muestra folios como pestañas y coordina guardar, cerrar, agregar, eliminar y mover folios desde la UI.
- Relaciones:
  - Contiene un `QETProject`.
  - Crea `DiagramView` para cada `Diagram`.
  - Empuja comandos como `RemoveDiagramCommand` y `MoveDiagramCommand` al `QUndoStack` del proyecto.
  - `ProjectView::save()` y `saveAs()` delegan en `doSave()`, que llama a `QETProject::write()`.
- Puntos importantes para colaboración:
  - Es el lugar UI donde aparecen los folios y su orden.
  - Es buen candidato para indicadores de estado por folio.
  - No es suficiente para sincronización, porque la persistencia real vive en `QETProject` y `Diagram`.

### `QETDiagramEditor`

- Header: `sources/qetdiagrameditor.h`
- Implementación: `sources/qetdiagrameditor.cpp`
- Responsabilidad: ventana principal del editor de esquemas.
- Relaciones:
  - Abre archivos `.qet` desde UI.
  - `openAndAddProject()` construye `QETProject` desde ruta.
  - `addProject()` crea `ProjectView` y registra el `QUndoStack` en un `QUndoGroup`.
  - `save()` y `saveAs()` delegan al `ProjectView` activo.
- Puntos importantes para colaboración:
  - Es la entrada UI para abrir/guardar.
  - El `QUndoGroup` hace activo el stack del proyecto actual.
  - Será importante no poner lógica colaborativa de negocio aquí; conviene mantenerlo como orquestador UI.

### `Element`

- Header: `sources/qetgraphicsitem/element.h`
- Implementación: `sources/qetgraphicsitem/element.cpp`
- Responsabilidad: clase base de elementos eléctricos colocados en un folio.
- Relaciones:
  - Hereda de `QetGraphicsItem`.
  - Contiene `Terminal`.
  - Se crea desde `ElementFactory` usando `ElementsLocation`.
  - Puede tener relaciones con otros elementos (`links_uuids`).
- Persistencia:
  - `Element::toXml()` escribe `type`, `uuid`, posición, orientación, terminales, información de elemento, textos dinámicos y enlaces.
  - `Element::fromXml()` lee el atributo `uuid`; si falta, crea uno.
- Puntos importantes para colaboración:
  - Tiene UUID persistente útil para operaciones futuras.
  - El tipo del elemento depende de la ubicación/colección (`type`), incluyendo `embed://`.

### `Conductor`

- Header: `sources/qetgraphicsitem/conductor.h`
- Implementación: `sources/qetgraphicsitem/conductor.cpp`
- Responsabilidad: conductor/cable que conecta dos terminales.
- Relaciones:
  - Hereda de `QGraphicsObject`.
  - Mantiene `terminal1` y `terminal2`.
  - Depende de `Terminal` y de propiedades de conductor.
- Persistencia:
  - `Conductor::toXml()` escribe endpoints.
  - En formato nuevo usa `element1`, `terminal1`, `element2`, `terminal2` con UUIDs de elemento/terminal.
  - En formato antiguo usa ids numéricos de terminal para compatibilidad.
  - No se observó UUID propio persistente para `Conductor`.
- Puntos importantes para colaboración:
  - Una operación sobre conductor se identifica naturalmente por el par de terminales.
  - Si se necesita historial/operaciones idempotentes por conductor, probablemente hará falta una estrategia adicional sin romper compatibilidad.

### `Terminal` y `TerminalData`

- Headers: `sources/qetgraphicsitem/terminal.h`, `sources/properties/terminaldata.h`
- Implementaciones: `sources/qetgraphicsitem/terminal.cpp`, `sources/properties/terminaldata.cpp`
- Responsabilidad: terminal física/lógica de un elemento, punto de conexión para conductores.
- Persistencia:
  - `TerminalData::toXml()` escribe `uuid`.
  - `TerminalData::fromXml()` lee `uuid` si existe.
  - El comentario en `TerminalData` explica que los UUIDs de terminal reemplazan el esquema antiguo basado en posición/id dinámico.
- Puntos importantes para colaboración:
  - La dupla `Element.uuid + Terminal.uuid` es el identificador más fuerte observado para endpoints de conductor.

## Flujo de carga de `.qet`

Flujo UI confirmado:

1. `QETDiagramEditor::openProject()` pide ruta con `QFileDialog`.
2. `QETDiagramEditor::openAndAddProject(filepath)` crea `new QETProject(filepath)`.
3. `QETProject::QETProject(const QString &path)` llama a `openFile(&file)`.
4. `QETProject::openFile(QFile *)` abre el archivo, crea `QDomDocument`, ejecuta `setContent(file)` y llama a `readProjectXml(xml_project)`.
5. `QETProject::readProjectXml()` valida raíz `<project>`, lee versión/título, propiedades globales, uso local, propiedades por defecto, plantillas de cartucho, colección embebida, folios, borneras, refresco y base de datos interna.
6. `QETProject::readDiagramsXml()` busca nodos `<diagram>`, crea `new Diagram(this)`, lo agrega a `m_diagrams_list`, conecta señales y llama a `diagram->initFromXml(diagram_xml_element)`.
7. `Diagram::initFromXml()` delega en `Diagram::fromXml()`.
8. `Diagram::fromXml()` lee propiedades del folio y luego reconstruye elementos, textos, imágenes, formas, tablas, terminal strip items y conductores.
9. Los conductores se reconstruyen después de los elementos, resolviendo terminales con `findTerminal()`.

Observación sobre orden:

- `QETProject::toXml()` escribe `order` en cada `<diagram>`.
- En el bloque revisado de `readDiagramsXml()` no se observó lectura ni ordenamiento por `order`; los folios se cargan en el orden del documento XML.

## Flujo de guardado

Flujo UI confirmado:

1. `QETDiagramEditor::save()` o `saveAs()` delega al `ProjectView` activo.
2. `ProjectView::save()` o `saveAs()` llega a `ProjectView::doSave()`.
3. `ProjectView::doSave()` llama a `m_project->write()`.
4. `QETProject::write()` llama a `QETProject::toXml()`.
5. `QETProject::toXml()` crea un `QDomDocument` con raíz `<project>`, agrega propiedades, defaults, todos los folios, borneras y colección embebida.
6. Cada folio se serializa con `diagram->toXml().documentElement()`.
7. El XML final se escribe con `QET::writeXmlFile()`.
8. `QET::writeXmlFile()` usa `QSaveFile`, `QTextStream`, UTF-8 sin BOM, indentación de 4 espacios y `commit()`.

Guardados adicionales:

- `QETProject` tiene backup de recuperación con `KAutoSaveFile`.
- `writeBackup()` también usa `toXml()` y escribe el proyecto completo, de forma asíncrona.
- Existe autosave configurable que llama a `write()`.

## Relación `QETProject -> Diagram`

Modelo confirmado:

- Un `QETProject` contiene cero o más `Diagram`.
- `QETProject::diagrams()` devuelve la lista de folios.
- `QETProject::folioIndex(const Diagram *)` calcula índice por posición en `m_diagrams_list`.
- `QETProject::addNewDiagram()` crea un `Diagram`, copia defaults de proyecto y empuja `AddDiagramCommand`.
- `QETProject::removeDiagram()` elimina inmediatamente, pero la UI usa normalmente `ProjectView::removeDiagram()` para empujar `RemoveDiagramCommand`.
- `QETProject::diagramOrderChanged()` mueve folios dentro de `m_diagrams_list`, actualiza datos de folio, marca modificado y emite señal.
- `ProjectView::loadDiagrams()` crea un `DiagramView` por cada `Diagram`.

Implicación:

- La unidad visual y de edición es `Diagram`.
- La unidad de archivo sigue siendo `QETProject`.
- El índice/orden del folio es importante en UI y en referencias de cartucho, pero no es un identificador estable suficiente para colaboración.

## Formato `.qet`

Estructura de alto nivel observada:

```xml
<project version="..." title="...">
    <titleblocktemplates>...</titleblocktemplates>
    <properties>...</properties>
    <newdiagrams>...</newdiagrams>
    <diagram order="1">...</diagram>
    <diagram order="2">...</diagram>
    <terminal_strips>...</terminal_strips>
    <collection>...</collection>
</project>
```

Dentro de un `<diagram>`:

- Propiedades de cartucho y borde.
- `<defaultconductor>`.
- Atributos como `conductorAutonum`, `freezeNewElement`, `freezeNewConductor`.
- Secuenciales por folio para elementos y conductores.
- `<elements>` con nodos `<element>`.
- `<conductors>` con nodos `<conductor>`.
- `<inputs>` para textos independientes.
- `<images>`.
- `<shapes>`.
- `<tables>`.
- Terminal strip items asociados al folio.

Respuesta inicial a la pregunta clave:

> ¿Es posible serializar, reemplazar o actualizar un único folio sin reconstruir conceptualmente todo el proyecto?

Parcialmente sí, con matices importantes:

- Confirmado: `Diagram::toXml()` serializa un único folio como `<diagram>`.
- Confirmado: `Diagram::fromXml()` puede construir/importar el contenido de un folio desde `<diagram>`.
- Confirmado: el archivo `.qet` almacena varios `<diagram>` bajo una raíz `<project>`.
- Confirmado: el flujo actual de guardado reconstruye y escribe el proyecto completo.
- Riesgo confirmado: no se observó un ID persistente de folio en XML. El orden del nodo y el atributo `order` no bastan para sincronización robusta.
- Riesgo confirmado: un folio puede depender de datos globales del proyecto: colección embebida, plantillas de cartucho, autonumeraciones, referencias cruzadas y borneras.

Conclusión: la colaboración por folio es viable como primera etapa si se bloquea un folio completo por usuario y se mantiene una autoridad clara para guardar el `.qet`. Para reemplazo parcial de folios dentro del XML, primero conviene introducir o mapear un identificador persistente de folio compatible hacia atrás, o usar una capa externa de metadatos mientras no se modifique el formato.

## IDs persistentes

### Proyecto

- `QETProject` tiene `QUuid m_uuid = QUuid::createUuid()`.
- `QETProject::uuid()` devuelve ese valor.
- No se observó que `QETProject::toXml()` escriba ese UUID al XML.
- `QETApp` registra proyectos abiertos con IDs enteros (`registerProject`, `projectId`, `project`) para uso runtime. Esos IDs parecen de sesión, no persistentes.

### Folio / `Diagram`

- `Diagram` tiene `QUuid m_uuid = QUuid::createUuid()`.
- `Diagram::uuid()` devuelve ese valor.
- No se observó que `Diagram::toXml()` escriba ese UUID al XML.
- `Diagram::toXml(false)` puede escribir `projectId`, pero esto es para copiar/pegar y apunta a un ID runtime de `QETApp`, no a un ID persistente de folio.
- `QETProject::toXml()` agrega `order`.

### Elementos

- `Element` tiene `QUuid m_uuid`.
- `Element::toXml()` escribe `uuid`.
- `Element::fromXml()` lee `uuid` y crea uno si falta.
- Los enlaces entre elementos se guardan en `links_uuids/link_uuid`.

### Terminales

- `TerminalData` tiene `QUuid m_uuid`.
- `TerminalData::toXml()` escribe `uuid`.
- `TerminalData::fromXml()` lee `uuid` si existe.
- `Terminal::uuid()` expone el UUID.

### Conductores

- No se observó UUID propio persistente para `Conductor`.
- Los conductores se serializan por endpoints:
  - Formato moderno: `element1 + terminal1 + element2 + terminal2`, con UUIDs.
  - Formato antiguo: IDs numéricos de terminal generados durante serialización.
- `Diagram::findTerminal()` resuelve endpoints modernos usando `Element.uuid` + `Terminal.uuid`, y conserva compatibilidad con IDs antiguos.

### Elementos embebidos

- `QETProject` posee `XmlElementCollection`.
- `QETProject::toXml()` escribe la raíz de la colección embebida (`<collection>`).
- `QETProject::readElementsCollectionXml()` lee el primer `<collection>` del proyecto.
- `Element::toXml()` escribe el tipo/ruta (`type`), que puede apuntar a `embed://`.
- `QETProject::importElement()` importa definiciones externas a la colección embebida.
- `QETProject::usesElement()` verifica si un elemento de colección se usa en algún diagrama.

### Referencias cruzadas

- Los vínculos entre elementos usan UUIDs persistentes de elemento.
- Los reportes de folio y elementos enlazados aparecen alrededor de `Element::linkedElements()` y `LinkElementCommand`.
- Para colaboración futura, las referencias cruzadas son un punto sensible: una edición en un folio puede afectar texto/estado de elementos relacionados en otro folio.

## Undo / Redo

Modelo confirmado:

- `QETProject` crea un `QUndoStack` por proyecto.
- `Diagram::undoStack()` devuelve el stack del proyecto.
- `QETDiagramEditor` mantiene un `QUndoGroup` para activar el stack del proyecto actual.
- La vista de Undo (`QUndoView`) se engancha al `QUndoGroup`.

Comandos principales confirmados en `sources/undocommand/`:

- `AddDiagramCommand`: agregar folio.
- `RemoveDiagramCommand`: eliminar folio.
- `MoveDiagramCommand`: mover/reordenar folio.
- `AddGraphicsObjectCommand`: agregar objeto gráfico a un folio.
- `DeleteQGraphicsItemCommand`: eliminar contenido gráfico de un folio.
- `MoveGraphicsItemCommand`: mover items gráficos.
- `RotateSelectionCommand`: rotar selección.
- `RotateTextsCommand`: rotar textos.
- `AddElementTextCommand` y comandos relacionados de grupos de textos.
- `ChangeElementInformationCommand`: modificar información de elemento.
- `ChangeElementDataCommand`: modificar datos de elemento.
- `ChangeTitleBlockCommand`: modificar cartucho.
- `ChangeBorderCommand`: modificar borde/dimensiones del folio.
- `ChangeConductorCommand`: modificar propiedades de conductor.
- `ResetConductorCommand`: resetear conductor.
- `LinkElementCommand`: enlazar/desenlazar elementos.
- `SetAutoNumContextCommand`: modificar contexto de autonumeración.
- `PasteDiagramCommand`: pegar contenido de diagrama.
- `MoveConductorsTextsCommand`: mover textos de conductores.
- `ChangeDiagramTextCommand`: modificar texto de diagrama.

Eventos interactivos relevantes:

- `diagrameventaddelement.cpp`: al agregar elemento puede crear un macro `QUndoCommand`, agregar el elemento y conductores relacionados.
- `diagrameventaddshape.cpp`: agrega formas con `AddGraphicsObjectCommand`.
- `diagrameventaddimage.cpp`: agrega imágenes con `AddGraphicsObjectCommand`.
- `diagrameventaddtext.cpp`: agrega textos con `AddGraphicsObjectCommand`.
- `diagrameventaddmacro.cpp`: pega macros con `PasteDiagramCommand`.

Implicación para colaboración:

- El historial actual ya modela muchas acciones como comandos.
- Pero los comandos son objetos C++ locales, no operaciones serializadas de sincronización.
- La granularidad del stack es por proyecto; para colaboración por folio habrá que filtrar o agrupar por `Diagram`.
- Algunas operaciones son claramente de folio; otras son de proyecto o pueden tocar referencias cruzadas entre folios.

## Experimento local de merge por folio

Archivos de prueba revisados el 2026-08-19:

- `C:\Users\jeykc\Documentos\Proyecto_Base.qet`: proyecto base con dos folios, cada uno con un recuadro.
- `C:\Users\jeykc\Documentos\Proyecto_01.qet`: edición del folio 1; el folio 2 permanece estructuralmente igual al base.
- `C:\Users\jeykc\Documentos\Proyecto_02.qet`: edición del folio 2; el folio 1 permanece estructuralmente igual al base.
- `C:\Users\jeykc\Documentos\Proyecto_Merge_01_02.qet`: archivo generado para prueba, combinando folio 1 desde `Proyecto_01.qet` y folio 2 desde `Proyecto_02.qet`.

Resultado confirmado por inspección XML:

- `Proyecto_01.qet` agrega un elemento en el folio 1:
  `embed://import/10_electric/10_allpole/110_network_supplies/3_pen_pravy.elmt`.
- `Proyecto_02.qet` agrega un elemento en el folio 2:
  `embed://import/10_electric/10_allpole/130_terminals_terminal_strips/barre_interconnexion_tn.elmt`.
- El archivo merge contiene ambos folios modificados y conserva dos nodos `<diagram>`.
- El folio 1 del merge es estructuralmente equivalente al folio 1 de `Proyecto_01.qet`.
- El folio 2 del merge es estructuralmente equivalente al folio 2 de `Proyecto_02.qet`.
- El merge debe incluir también los elementos embebidos correspondientes dentro de `/project/collection`; reemplazar solo `<diagram>` no basta.

Conclusión del experimento:

- Para ediciones simples e independientes, el contenido del folio se puede fusionar a nivel de nodo `<diagram>` sin cambiar el formato `.qet`.
- La primera capa de colaboración por folio no debe tratar el folio como unidad totalmente aislada; debe calcular también dependencias globales del proyecto, especialmente `<collection>`.
- Este experimento apoya la viabilidad de una primera iteración conservadora: detectar el folio modificado, reemplazar ese `<diagram>` en una copia base/controlada y fusionar dependencias globales necesarias.
- Aún no queda resuelto el caso de conflictos globales: título del proyecto, propiedades, autonumeraciones, borneras, referencias cruzadas, plantillas de cartucho, reordenamiento o eliminación de folios.

## Experimento local con conductores

Archivos de prueba revisados el 2026-08-19:

- `C:\Users\jeykc\Documentos\Conexion_Base.qet`: proyecto base con dos folios.
- `C:\Users\jeykc\Documentos\Conexion_01.qet`: edición del folio 1; contiene dos elementos `3_pen_pravy.elmt` y cuatro conductores.
- `C:\Users\jeykc\Documentos\Conexion_02.qet`: edición del folio 2; contiene dos elementos `src_1pn.elmt` y dos conductores.
- `C:\Users\jeykc\Documentos\GitHub\qelectrotech-source-mirror\build\qet-merge-tests\Conexion_Merge_Tool_01_02.qet`: archivo generado por la herramienta de merge.

Resultado confirmado por inspección XML y por `tools/qet_folio_merge.py analyze`:

- El merge conserva `Conexion_Base` como raíz global del proyecto.
- El folio `order:1` del merge queda estructuralmente equivalente al folio 1 de `Conexion_01.qet`.
- El folio `order:2` del merge queda estructuralmente equivalente al folio 2 de `Conexion_02.qet`.
- `/project/collection` contiene los dos elementos embebidos necesarios: `3_pen_pravy.elmt` y `src_1pn.elmt`.
- Todos los conductores del merge fueron validados como `ok` por la herramienta: 4 en el folio 1 y 2 en el folio 2.

Validación posterior desde QET:

- El usuario abrió `Conexion_Merge_Tool_01_02.qet` desde el build del repo y confirmó visualmente que ambos folios estaban operativos.
- El archivo fue guardado desde QET como `C:\Users\jeykc\Documentos\GitHub\qelectrotech-source-mirror\build\qet-merge-tests\Conexion_Merge_Guardado_QET.qet`.
- Al comparar una salida fresca de la herramienta (`Conexion_Merge_Tool_01_02_Fresh.qet`) contra el archivo guardado por QET:
  - los elementos del folio `order:1` siguen siendo equivalentes por UUID, tipo y posición;
  - los conductores del folio `order:1` siguen siendo equivalentes por endpoints;
  - los elementos del folio `order:2` siguen siendo equivalentes por UUID, tipo y posición;
  - los conductores del folio `order:2` siguen siendo equivalentes por endpoints;
  - todos los conductores del archivo guardado siguen siendo válidos.
- QET reordena algunos nodos internos al guardar, por lo que una comparación estructural estricta de XML puede cambiar aunque la semántica del folio se conserve.
- QET también amplió `/project/collection` con elementos embebidos adicionales relacionados: `act_termique_no_esclave.elmt`, `act_thermique_nf_esclave.elmt`, `comm_thermique.elmt`, `dis_mag_term_4f-1.elmt` y `fa4202_disjoncteur_moteur_3p.elmt`.
- La colección guardada por QET sigue siendo un superset de la colección mínima generada por la herramienta.

Observación importante sobre conductores:

- Los nodos `<conductor>` modernos referencian `element1`, `terminal1`, `element2` y `terminal2`.
- `element1` y `element2` apuntan a UUIDs de instancias `<element>` dentro del mismo folio.
- `terminal1` y `terminal2` apuntan a UUIDs de terminal definidos dentro de la definición embebida del elemento en `/project/collection`.
- Por eso, un merge por folio que incluya conductores debe fusionar también la colección embebida relacionada; copiar solo el nodo `<diagram>` puede dejar referencias incompletas.

Conclusión del experimento:

- La estrategia de reemplazar folios completos es viable también para conductores locales al folio, siempre que sus elementos embebidos se conserven en `/project/collection`.
- La herramienta offline ya puede detectar si un conductor queda apuntando a un elemento inexistente o a un terminal embebido inexistente.

## Herramienta inicial de análisis/merge

Archivo agregado:

- `tools/qet_folio_merge.py`
- `tools/qet_collab_session.py`

Función:

- Analiza proyectos `.qet` sin modificar QElectroTech.
- Identifica folios por `order` de forma predeterminada, con fallback opcional por posición.
- Calcula una huella estructural de cada `<diagram>` ignorando diferencias de indentación/orden textual no relevantes.
- Detecta qué folios cambiaron contra un archivo base.
- Rechaza el merge si dos variantes modifican el mismo folio con contenido distinto.
- Fusiona de forma aditiva `/project/collection` para conservar elementos embebidos requeridos por los folios importados.
- Valida endpoints de conductores contra elementos del folio y terminales de elementos embebidos cuando están disponibles en `/project/collection`.
- Conserva las secciones globales desde el archivo base, pero reporta diferencias globales como advertencias.
- Crea sesiones colaborativas offline con `checkout`, `submit` y `merge`, usando manifiestos sidecar `.jwqet.json` para mapear maestro, baseline, copia local y entrega sin tocar el formato `.qet`.

Comandos usados en esta PC:

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_folio_merge.py analyze C:\Users\jeykc\Documentos\Proyecto_Base.qet C:\Users\jeykc\Documentos\Proyecto_01.qet C:\Users\jeykc\Documentos\Proyecto_02.qet
```

```powershell
C:\msys64\ucrt64\bin\python.exe tools\qet_folio_merge.py merge --base C:\Users\jeykc\Documentos\Proyecto_Base.qet --output build\qet-merge-tests\Proyecto_Merge_Tool_01_02.qet --force C:\Users\jeykc\Documentos\Proyecto_01.qet C:\Users\jeykc\Documentos\Proyecto_02.qet
```

Prueba agregada:

- `tests/qet_folio_merge_test.py`
- `tests/qet_collab_session_test.py`
- Ejecutada con:

```powershell
C:\msys64\ucrt64\bin\python.exe -m unittest tests\qet_folio_merge_test.py tests\qet_collab_session_test.py
```

Resultado de validación:

- `analyze` detecta que `Proyecto_01.qet` cambia `order:1`.
- `analyze` detecta que `Proyecto_02.qet` cambia `order:2`.
- `merge` genera `build\qet-merge-tests\Proyecto_Merge_Tool_01_02.qet`.
- El output contiene los dos folios modificados y dos elementos embebidos en `/project/collection`.
- El archivo fue abierto y guardado nuevamente desde QElectroTech como `build\qet-merge-tests\Proyecto_Merge_Guardado_QET.qet`.
- Después de guardar desde QET, los dos folios siguen siendo equivalentes al output de la herramienta.
- Después de guardar desde QET, `/project/collection` sigue siendo equivalente al output de la herramienta.
- QET normaliza algunos detalles no funcionales al guardar:
  - puede omitir `<elementInformations/>` vacío en elementos;
  - puede cambiar saltos de línea dentro de textos de metadatos de elementos embebidos;
  - actualiza/normaliza secciones globales como `<properties>`, `<usage>` y `<newdiagrams>`.
- Las pruebas unitarias mínimas pasan y cubren merge de folios distintos, rechazo de conflicto en el mismo folio, normalizaciones observadas al guardar desde QET, validación de endpoints de conductores y flujo colaborativo `checkout`/`submit`/`merge` con manifiestos.

Nota de ejecución en Windows:

- Si el `.qet` se abre con doble clic, Windows puede usar la instalación local de QElectroTech en `C:\Program Files\QElectroTech\bin\qelectrotech.exe`.
- En esta PC esa instalación reporta una versión anterior (`0.100.0`), por lo que muestra un aviso al abrir archivos guardados como `0.200.1`.
- Para validar el fork compilado, abrir los proyectos desde `build\jw-qet-qt5-nokf\run-qelectrotech.bat` o ejecutar directamente el binario del build con los argumentos de rutas comunes.

Límites actuales de la herramienta:

- No resuelve reordenamiento, creación o eliminación de folios.
- No resuelve conflictos globales; solo los reporta.
- No elimina elementos embebidos no usados.
- No introduce IDs persistentes de folio.
- No debe considerarse todavía un mecanismo de colaboración en vivo; es una herramienta de verificación y merge offline.

## Primeras conclusiones

Confirmado:

- La arquitectura ya separa proyecto (`QETProject`), folio/escena (`Diagram`) y vista (`DiagramView`).
- El formato `.qet` contiene folios como nodos XML independientes bajo `<project>`.
- `Diagram::toXml()` y `Diagram::fromXml()` son puntos naturales para serialización/deserialización por folio.
- El guardado oficial actual sigue siendo de proyecto completo.
- Elementos y terminales tienen UUIDs persistentes útiles.
- Conductores no tienen UUID propio; se identifican por endpoints.
- Proyecto y folio tienen UUIDs en memoria, pero no se confirmó persistencia en `.qet`.

Riesgos para colaboración por folio:

- Falta de ID persistente de folio.
- Guardado completo del archivo puede sobrescribir cambios si dos PCs guardan versiones divergentes.
- Referencias cruzadas, autonumeración y borneras pueden cruzar límites de folio.
- El `QUndoStack` es por proyecto, no por folio.
- La colección embebida es global al proyecto: agregar un elemento nuevo desde un folio puede requerir actualizar `<collection>`.

Viabilidad inicial:

- Sí es viable empezar con colaboración controlada por folio, sin edición simultánea del mismo folio.
- La estrategia inicial debería bloquear folios completos y serializar cambios por folio, manteniendo un merge conservador sobre el XML del proyecto.
- Antes de implementar locks o servidor, el siguiente paso técnico debería ser formalizar pruebas/herramientas mínimas para detectar folios cambiados, fusionar `<diagram>` y fusionar dependencias globales conocidas.
- Flujo operativo MVP elegido: carpeta compartida tipo Google Drive con maestro publicado y copias locales por usuario; GitHub queda para versionar el código del fork y posible respaldo posterior. La herramienta puente es `tools/qet_collab_session.py`. Ver `docs/collaboration/JW_QET_MVP_WORKFLOW.md`.
- Validación local del MVP completada en `build\qet-collab-mvp`: una ronda exitosa publicó `JW_QET_COLLAB\04_PUBLISHED\Proyecto_Publicado.qet`; una ronda conflictiva en `JW_QET_CONFLICT` rechazó publicar cuando dos usuarios modificaron el mismo folio.
- Workspace real de Google Drive configurado en `H:\Mi unidad\01_JW_CONTROL\04_PRODUCTOS\03_ACTIVOS\JWPLC_LAUNDRY\03_IMPLEMENTACIONES_CLIENTE\2026-008_KOKETA\02_DIAGRAMA_ELECTRICO\JW_QET_COLLAB`, con maestro inicial en `00_MASTER\Proyecto.qet` y copia de trabajo para `jeykc` en `02_WORKING\jeykc`.
- Primer puente UI agregado en `QETDiagramEditor`: `Archivo > Crear copia de trabajo colaborativa...` ejecuta `checkout` y abre la copia local; `Archivo > Entregar cambios colaborativos...` guarda el proyecto activo y ejecuta `submit`. La fusion/publicacion sigue fuera de QET en esta iteracion.

## Siguientes pasos propuestos

1. Validar desde QET el checkout y submit contra la carpeta real de Google Drive.
2. Probar casos reales adicionales: textos, referencias cruzadas, autonumeración y borneras.
3. Revisar si existe alguna capa ya hecha para exportar/importar folios individuales desde UI o CLI.
4. Definir una propuesta mínima de ID persistente de folio o metadata externa, sin romper compatibilidad `.qet`.
5. Recién después, diseñar el primer mecanismo de prevención de sobrescritura por folio.
