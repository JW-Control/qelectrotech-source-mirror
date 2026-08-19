/****************************************************************************
** Meta object code from reading C++ file 'qetdiagrameditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qetdiagrameditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qetdiagrameditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QETDiagramEditor_t {
    QByteArrayData data[65];
    char stringdata0[1089];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QETDiagramEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QETDiagramEditor_t qt_meta_stringdata_QETDiagramEditor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QETDiagramEditor"
QT_MOC_LITERAL(1, 17, 17), // "syncElementsPanel"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 4), // "save"
QT_MOC_LITERAL(4, 41, 6), // "saveAs"
QT_MOC_LITERAL(5, 48, 10), // "newProject"
QT_MOC_LITERAL(6, 59, 11), // "openProject"
QT_MOC_LITERAL(7, 71, 30), // "createCollaborativeWorkingCopy"
QT_MOC_LITERAL(8, 102, 26), // "submitCollaborativeChanges"
QT_MOC_LITERAL(9, 129, 14), // "openRecentFile"
QT_MOC_LITERAL(10, 144, 12), // "closeProject"
QT_MOC_LITERAL(11, 157, 12), // "ProjectView*"
QT_MOC_LITERAL(12, 170, 11), // "QETProject*"
QT_MOC_LITERAL(13, 182, 18), // "zoomGroupTriggered"
QT_MOC_LITERAL(14, 201, 8), // "QAction*"
QT_MOC_LITERAL(15, 210, 6), // "action"
QT_MOC_LITERAL(16, 217, 20), // "selectGroupTriggered"
QT_MOC_LITERAL(17, 238, 21), // "addItemGroupTriggered"
QT_MOC_LITERAL(18, 260, 23), // "selectionGroupTriggered"
QT_MOC_LITERAL(19, 284, 23), // "rowColumnGroupTriggered"
QT_MOC_LITERAL(20, 308, 18), // "slot_updateActions"
QT_MOC_LITERAL(21, 327, 20), // "slot_updateUndoStack"
QT_MOC_LITERAL(22, 348, 22), // "slot_updateModeActions"
QT_MOC_LITERAL(23, 371, 25), // "slot_updateComplexActions"
QT_MOC_LITERAL(24, 397, 22), // "slot_updatePasteAction"
QT_MOC_LITERAL(25, 420, 22), // "slot_updateWindowsMenu"
QT_MOC_LITERAL(26, 443, 22), // "slot_updateAutoNumDock"
QT_MOC_LITERAL(27, 466, 21), // "generateTerminalBlock"
QT_MOC_LITERAL(28, 488, 15), // "setWindowedMode"
QT_MOC_LITERAL(29, 504, 13), // "setTabbedMode"
QT_MOC_LITERAL(30, 518, 12), // "readSettings"
QT_MOC_LITERAL(31, 531, 13), // "writeSettings"
QT_MOC_LITERAL(32, 545, 15), // "activateProject"
QT_MOC_LITERAL(33, 561, 14), // "activateWidget"
QT_MOC_LITERAL(34, 576, 8), // "QWidget*"
QT_MOC_LITERAL(35, 585, 16), // "projectWasClosed"
QT_MOC_LITERAL(36, 602, 21), // "editProjectProperties"
QT_MOC_LITERAL(37, 624, 22), // "slot_terminalNumbering"
QT_MOC_LITERAL(38, 647, 21), // "editDiagramProperties"
QT_MOC_LITERAL(39, 669, 12), // "DiagramView*"
QT_MOC_LITERAL(40, 682, 8), // "Diagram*"
QT_MOC_LITERAL(41, 691, 19), // "addDiagramToProject"
QT_MOC_LITERAL(42, 711, 21), // "addDiagramToProjectAt"
QT_MOC_LITERAL(43, 733, 13), // "removeDiagram"
QT_MOC_LITERAL(44, 747, 14), // "removeDiagrams"
QT_MOC_LITERAL(45, 762, 15), // "QList<Diagram*>"
QT_MOC_LITERAL(46, 778, 8), // "diagrams"
QT_MOC_LITERAL(47, 787, 24), // "removeDiagramFromProject"
QT_MOC_LITERAL(48, 812, 13), // "moveDiagramUp"
QT_MOC_LITERAL(49, 826, 15), // "moveDiagramDown"
QT_MOC_LITERAL(50, 842, 16), // "moveDiagramUpTop"
QT_MOC_LITERAL(51, 859, 16), // "moveDiagramUpx10"
QT_MOC_LITERAL(52, 876, 18), // "moveDiagramDownx10"
QT_MOC_LITERAL(53, 895, 17), // "moveDiagramUpx100"
QT_MOC_LITERAL(54, 913, 19), // "moveDiagramDownx100"
QT_MOC_LITERAL(55, 933, 21), // "reloadOldElementPanel"
QT_MOC_LITERAL(56, 955, 15), // "diagramWasAdded"
QT_MOC_LITERAL(57, 971, 18), // "findElementInPanel"
QT_MOC_LITERAL(58, 990, 16), // "ElementsLocation"
QT_MOC_LITERAL(59, 1007, 9), // "showError"
QT_MOC_LITERAL(60, 1017, 9), // "QETResult"
QT_MOC_LITERAL(61, 1027, 18), // "subWindowActivated"
QT_MOC_LITERAL(62, 1046, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(63, 1061, 10), // "subWindows"
QT_MOC_LITERAL(64, 1072, 16) // "selectionChanged"

    },
    "QETDiagramEditor\0syncElementsPanel\0\0"
    "save\0saveAs\0newProject\0openProject\0"
    "createCollaborativeWorkingCopy\0"
    "submitCollaborativeChanges\0openRecentFile\0"
    "closeProject\0ProjectView*\0QETProject*\0"
    "zoomGroupTriggered\0QAction*\0action\0"
    "selectGroupTriggered\0addItemGroupTriggered\0"
    "selectionGroupTriggered\0rowColumnGroupTriggered\0"
    "slot_updateActions\0slot_updateUndoStack\0"
    "slot_updateModeActions\0slot_updateComplexActions\0"
    "slot_updatePasteAction\0slot_updateWindowsMenu\0"
    "slot_updateAutoNumDock\0generateTerminalBlock\0"
    "setWindowedMode\0setTabbedMode\0"
    "readSettings\0writeSettings\0activateProject\0"
    "activateWidget\0QWidget*\0projectWasClosed\0"
    "editProjectProperties\0slot_terminalNumbering\0"
    "editDiagramProperties\0DiagramView*\0"
    "Diagram*\0addDiagramToProject\0"
    "addDiagramToProjectAt\0removeDiagram\0"
    "removeDiagrams\0QList<Diagram*>\0diagrams\0"
    "removeDiagramFromProject\0moveDiagramUp\0"
    "moveDiagramDown\0moveDiagramUpTop\0"
    "moveDiagramUpx10\0moveDiagramDownx10\0"
    "moveDiagramUpx100\0moveDiagramDownx100\0"
    "reloadOldElementPanel\0diagramWasAdded\0"
    "findElementInPanel\0ElementsLocation\0"
    "showError\0QETResult\0subWindowActivated\0"
    "QMdiSubWindow*\0subWindows\0selectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QETDiagramEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  289,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  290,    2, 0x0a /* Public */,
       4,    0,  291,    2, 0x0a /* Public */,
       5,    0,  292,    2, 0x0a /* Public */,
       6,    0,  293,    2, 0x0a /* Public */,
       7,    0,  294,    2, 0x0a /* Public */,
       8,    0,  295,    2, 0x0a /* Public */,
       9,    1,  296,    2, 0x0a /* Public */,
      10,    1,  299,    2, 0x0a /* Public */,
      10,    1,  302,    2, 0x0a /* Public */,
      13,    1,  305,    2, 0x0a /* Public */,
      16,    1,  308,    2, 0x0a /* Public */,
      17,    1,  311,    2, 0x0a /* Public */,
      18,    1,  314,    2, 0x0a /* Public */,
      19,    1,  317,    2, 0x0a /* Public */,
      20,    0,  320,    2, 0x0a /* Public */,
      21,    0,  321,    2, 0x0a /* Public */,
      22,    0,  322,    2, 0x0a /* Public */,
      23,    0,  323,    2, 0x0a /* Public */,
      24,    0,  324,    2, 0x0a /* Public */,
      25,    0,  325,    2, 0x0a /* Public */,
      26,    0,  326,    2, 0x0a /* Public */,
      27,    0,  327,    2, 0x0a /* Public */,
      28,    0,  328,    2, 0x0a /* Public */,
      29,    0,  329,    2, 0x0a /* Public */,
      30,    0,  330,    2, 0x0a /* Public */,
      31,    0,  331,    2, 0x0a /* Public */,
      32,    1,  332,    2, 0x0a /* Public */,
      32,    1,  335,    2, 0x0a /* Public */,
      33,    1,  338,    2, 0x0a /* Public */,
      35,    1,  341,    2, 0x0a /* Public */,
      36,    1,  344,    2, 0x0a /* Public */,
      36,    1,  347,    2, 0x0a /* Public */,
      37,    0,  350,    2, 0x0a /* Public */,
      38,    1,  351,    2, 0x0a /* Public */,
      38,    1,  354,    2, 0x0a /* Public */,
      41,    1,  357,    2, 0x0a /* Public */,
      42,    2,  360,    2, 0x0a /* Public */,
      43,    1,  365,    2, 0x0a /* Public */,
      44,    1,  368,    2, 0x0a /* Public */,
      47,    0,  371,    2, 0x0a /* Public */,
      48,    1,  372,    2, 0x0a /* Public */,
      49,    1,  375,    2, 0x0a /* Public */,
      50,    1,  378,    2, 0x0a /* Public */,
      51,    1,  381,    2, 0x0a /* Public */,
      52,    1,  384,    2, 0x0a /* Public */,
      53,    1,  387,    2, 0x0a /* Public */,
      54,    1,  390,    2, 0x0a /* Public */,
      55,    0,  393,    2, 0x0a /* Public */,
      56,    1,  394,    2, 0x0a /* Public */,
      57,    1,  397,    2, 0x0a /* Public */,
      59,    1,  400,    2, 0x0a /* Public */,
      59,    1,  403,    2, 0x0a /* Public */,
      61,    1,  406,    2, 0x0a /* Public */,
      64,    0,  409,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    2,
    QMetaType::Bool, 0x80000000 | 11,    2,
    QMetaType::Bool, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 34,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 39,    2,
    QMetaType::Void, 0x80000000 | 40,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 40,    2,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 39,    2,
    QMetaType::Void, 0x80000000 | 58,    2,
    QMetaType::Void, 0x80000000 | 60,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 62,   63,
    QMetaType::Void,

       0        // eod
};

void QETDiagramEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QETDiagramEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->syncElementsPanel(); break;
        case 1: _t->save(); break;
        case 2: _t->saveAs(); break;
        case 3: { bool _r = _t->newProject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->openProject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->createCollaborativeWorkingCopy(); break;
        case 6: _t->submitCollaborativeChanges(); break;
        case 7: { bool _r = _t->openRecentFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->closeProject((*reinterpret_cast< ProjectView*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->closeProject((*reinterpret_cast< QETProject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->zoomGroupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 11: _t->selectGroupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 12: _t->addItemGroupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 13: _t->selectionGroupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 14: _t->rowColumnGroupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 15: _t->slot_updateActions(); break;
        case 16: _t->slot_updateUndoStack(); break;
        case 17: _t->slot_updateModeActions(); break;
        case 18: _t->slot_updateComplexActions(); break;
        case 19: _t->slot_updatePasteAction(); break;
        case 20: _t->slot_updateWindowsMenu(); break;
        case 21: _t->slot_updateAutoNumDock(); break;
        case 22: _t->generateTerminalBlock(); break;
        case 23: _t->setWindowedMode(); break;
        case 24: _t->setTabbedMode(); break;
        case 25: _t->readSettings(); break;
        case 26: _t->writeSettings(); break;
        case 27: _t->activateProject((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 28: _t->activateProject((*reinterpret_cast< ProjectView*(*)>(_a[1]))); break;
        case 29: _t->activateWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 30: _t->projectWasClosed((*reinterpret_cast< ProjectView*(*)>(_a[1]))); break;
        case 31: _t->editProjectProperties((*reinterpret_cast< ProjectView*(*)>(_a[1]))); break;
        case 32: _t->editProjectProperties((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 33: _t->slot_terminalNumbering(); break;
        case 34: _t->editDiagramProperties((*reinterpret_cast< DiagramView*(*)>(_a[1]))); break;
        case 35: _t->editDiagramProperties((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 36: _t->addDiagramToProject((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 37: _t->addDiagramToProjectAt((*reinterpret_cast< QETProject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->removeDiagram((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 39: _t->removeDiagrams((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 40: _t->removeDiagramFromProject(); break;
        case 41: _t->moveDiagramUp((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 42: _t->moveDiagramDown((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 43: _t->moveDiagramUpTop((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 44: _t->moveDiagramUpx10((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 45: _t->moveDiagramDownx10((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 46: _t->moveDiagramUpx100((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 47: _t->moveDiagramDownx100((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 48: _t->reloadOldElementPanel(); break;
        case 49: _t->diagramWasAdded((*reinterpret_cast< DiagramView*(*)>(_a[1]))); break;
        case 50: _t->findElementInPanel((*reinterpret_cast< const ElementsLocation(*)>(_a[1]))); break;
        case 51: _t->showError((*reinterpret_cast< const QETResult(*)>(_a[1]))); break;
        case 52: _t->showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 53: _t->subWindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 54: _t->selectionChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 50:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ElementsLocation >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QETDiagramEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QETDiagramEditor::syncElementsPanel)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QETDiagramEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QETMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QETDiagramEditor.data,
    qt_meta_data_QETDiagramEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QETDiagramEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QETDiagramEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QETDiagramEditor.stringdata0))
        return static_cast<void*>(this);
    return QETMainWindow::qt_metacast(_clname);
}

int QETDiagramEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QETMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    }
    return _id;
}

// SIGNAL 0
void QETDiagramEditor::syncElementsPanel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
