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
- Antes de implementar locks o servidor, el siguiente paso técnico debería ser compilar el QElectroTech original y luego crear pruebas/herramientas mínimas para comparar `Diagram::toXml()` contra nodos `<diagram>` reales.

## Siguientes pasos propuestos

1. Reparar/instalar dependencias de MSYS2 UCRT64 y compilar QElectroTech original sin cambios funcionales.
2. Confirmar en una muestra `.qet` real cómo se ven:
   - `<project>`
   - `<diagram order="...">`
   - UUIDs de elementos
   - UUIDs de terminales
   - conductores por endpoints
   - colección embebida
3. Revisar si existe alguna capa ya hecha para exportar/importar folios individuales desde UI o CLI.
4. Definir una propuesta mínima de ID persistente de folio o metadata externa, sin romper compatibilidad `.qet`.
5. Recién después, diseñar el primer mecanismo de prevención de sobrescritura por folio.
