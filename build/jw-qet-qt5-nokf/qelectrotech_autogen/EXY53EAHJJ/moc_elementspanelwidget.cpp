/****************************************************************************
** Meta object code from reading C++ file 'elementspanelwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/elementspanelwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementspanelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementsPanelWidget_t {
    QByteArrayData data[46];
    char stringdata0[926];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementsPanelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementsPanelWidget_t qt_meta_stringdata_ElementsPanelWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ElementsPanelWidget"
QT_MOC_LITERAL(1, 20, 17), // "requestForProject"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 11), // "QETProject*"
QT_MOC_LITERAL(4, 51, 20), // "requestForNewDiagram"
QT_MOC_LITERAL(5, 72, 22), // "requestForNewDiagramAt"
QT_MOC_LITERAL(6, 95, 24), // "requestForProjectClosing"
QT_MOC_LITERAL(7, 120, 34), // "requestForProjectPropertiesEd..."
QT_MOC_LITERAL(8, 155, 34), // "requestForDiagramPropertiesEd..."
QT_MOC_LITERAL(9, 190, 8), // "Diagram*"
QT_MOC_LITERAL(10, 199, 25), // "requestForDiagramDeletion"
QT_MOC_LITERAL(11, 225, 26), // "requestForDiagramsDeletion"
QT_MOC_LITERAL(12, 252, 15), // "QList<Diagram*>"
QT_MOC_LITERAL(13, 268, 8), // "diagrams"
QT_MOC_LITERAL(14, 277, 23), // "requestForDiagramMoveUp"
QT_MOC_LITERAL(15, 301, 25), // "requestForDiagramMoveDown"
QT_MOC_LITERAL(16, 327, 26), // "requestForDiagramMoveUpTop"
QT_MOC_LITERAL(17, 354, 26), // "requestForDiagramMoveUpx10"
QT_MOC_LITERAL(18, 381, 27), // "requestForDiagramMoveUpx100"
QT_MOC_LITERAL(19, 409, 28), // "requestForDiagramMoveDownx10"
QT_MOC_LITERAL(20, 438, 29), // "requestForDiagramMoveDownx100"
QT_MOC_LITERAL(21, 468, 28), // "openDirectoryForSelectedItem"
QT_MOC_LITERAL(22, 497, 23), // "copyPathForSelectedItem"
QT_MOC_LITERAL(23, 521, 15), // "reloadAndFilter"
QT_MOC_LITERAL(24, 537, 15), // "activateProject"
QT_MOC_LITERAL(25, 553, 12), // "closeProject"
QT_MOC_LITERAL(26, 566, 21), // "editProjectProperties"
QT_MOC_LITERAL(27, 588, 21), // "editDiagramProperties"
QT_MOC_LITERAL(28, 610, 10), // "newDiagram"
QT_MOC_LITERAL(29, 621, 18), // "insertDiagramAbove"
QT_MOC_LITERAL(30, 640, 18), // "insertDiagramBelow"
QT_MOC_LITERAL(31, 659, 13), // "deleteDiagram"
QT_MOC_LITERAL(32, 673, 16), // "duplicateDiagram"
QT_MOC_LITERAL(33, 690, 13), // "moveDiagramUp"
QT_MOC_LITERAL(34, 704, 15), // "moveDiagramDown"
QT_MOC_LITERAL(35, 720, 16), // "moveDiagramUpTop"
QT_MOC_LITERAL(36, 737, 16), // "moveDiagramUpx10"
QT_MOC_LITERAL(37, 754, 17), // "moveDiagramUpx100"
QT_MOC_LITERAL(38, 772, 18), // "moveDiagramDownx10"
QT_MOC_LITERAL(39, 791, 19), // "moveDiagramDownx100"
QT_MOC_LITERAL(40, 811, 21), // "addTitleBlockTemplate"
QT_MOC_LITERAL(41, 833, 22), // "editTitleBlockTemplate"
QT_MOC_LITERAL(42, 856, 24), // "removeTitleBlockTemplate"
QT_MOC_LITERAL(43, 881, 13), // "updateButtons"
QT_MOC_LITERAL(44, 895, 17), // "handleContextMenu"
QT_MOC_LITERAL(45, 913, 12) // "filterEdited"

    },
    "ElementsPanelWidget\0requestForProject\0"
    "\0QETProject*\0requestForNewDiagram\0"
    "requestForNewDiagramAt\0requestForProjectClosing\0"
    "requestForProjectPropertiesEdition\0"
    "requestForDiagramPropertiesEdition\0"
    "Diagram*\0requestForDiagramDeletion\0"
    "requestForDiagramsDeletion\0QList<Diagram*>\0"
    "diagrams\0requestForDiagramMoveUp\0"
    "requestForDiagramMoveDown\0"
    "requestForDiagramMoveUpTop\0"
    "requestForDiagramMoveUpx10\0"
    "requestForDiagramMoveUpx100\0"
    "requestForDiagramMoveDownx10\0"
    "requestForDiagramMoveDownx100\0"
    "openDirectoryForSelectedItem\0"
    "copyPathForSelectedItem\0reloadAndFilter\0"
    "activateProject\0closeProject\0"
    "editProjectProperties\0editDiagramProperties\0"
    "newDiagram\0insertDiagramAbove\0"
    "insertDiagramBelow\0deleteDiagram\0"
    "duplicateDiagram\0moveDiagramUp\0"
    "moveDiagramDown\0moveDiagramUpTop\0"
    "moveDiagramUpx10\0moveDiagramUpx100\0"
    "moveDiagramDownx10\0moveDiagramDownx100\0"
    "addTitleBlockTemplate\0editTitleBlockTemplate\0"
    "removeTitleBlockTemplate\0updateButtons\0"
    "handleContextMenu\0filterEdited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementsPanelWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x06 /* Public */,
       4,    1,  217,    2, 0x06 /* Public */,
       5,    2,  220,    2, 0x06 /* Public */,
       6,    1,  225,    2, 0x06 /* Public */,
       7,    1,  228,    2, 0x06 /* Public */,
       8,    1,  231,    2, 0x06 /* Public */,
      10,    1,  234,    2, 0x06 /* Public */,
      11,    1,  237,    2, 0x06 /* Public */,
      14,    1,  240,    2, 0x06 /* Public */,
      15,    1,  243,    2, 0x06 /* Public */,
      16,    1,  246,    2, 0x06 /* Public */,
      17,    1,  249,    2, 0x06 /* Public */,
      18,    1,  252,    2, 0x06 /* Public */,
      19,    1,  255,    2, 0x06 /* Public */,
      20,    1,  258,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    0,  261,    2, 0x0a /* Public */,
      22,    0,  262,    2, 0x0a /* Public */,
      23,    0,  263,    2, 0x0a /* Public */,
      24,    0,  264,    2, 0x0a /* Public */,
      25,    0,  265,    2, 0x0a /* Public */,
      26,    0,  266,    2, 0x0a /* Public */,
      27,    0,  267,    2, 0x0a /* Public */,
      28,    0,  268,    2, 0x0a /* Public */,
      29,    0,  269,    2, 0x0a /* Public */,
      30,    0,  270,    2, 0x0a /* Public */,
      31,    0,  271,    2, 0x0a /* Public */,
      32,    0,  272,    2, 0x0a /* Public */,
      33,    0,  273,    2, 0x0a /* Public */,
      34,    0,  274,    2, 0x0a /* Public */,
      35,    0,  275,    2, 0x0a /* Public */,
      36,    0,  276,    2, 0x0a /* Public */,
      37,    0,  277,    2, 0x0a /* Public */,
      38,    0,  278,    2, 0x0a /* Public */,
      39,    0,  279,    2, 0x0a /* Public */,
      40,    0,  280,    2, 0x0a /* Public */,
      41,    0,  281,    2, 0x0a /* Public */,
      42,    0,  282,    2, 0x0a /* Public */,
      43,    0,  283,    2, 0x0a /* Public */,
      44,    1,  284,    2, 0x0a /* Public */,
      45,    1,  287,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
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
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ElementsPanelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementsPanelWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->requestForProject((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 1: _t->requestForNewDiagram((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 2: _t->requestForNewDiagramAt((*reinterpret_cast< QETProject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->requestForProjectClosing((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 4: _t->requestForProjectPropertiesEdition((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 5: _t->requestForDiagramPropertiesEdition((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 6: _t->requestForDiagramDeletion((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 7: _t->requestForDiagramsDeletion((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 8: _t->requestForDiagramMoveUp((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 9: _t->requestForDiagramMoveDown((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 10: _t->requestForDiagramMoveUpTop((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 11: _t->requestForDiagramMoveUpx10((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 12: _t->requestForDiagramMoveUpx100((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 13: _t->requestForDiagramMoveDownx10((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 14: _t->requestForDiagramMoveDownx100((*reinterpret_cast< const QList<Diagram*>(*)>(_a[1]))); break;
        case 15: _t->openDirectoryForSelectedItem(); break;
        case 16: _t->copyPathForSelectedItem(); break;
        case 17: _t->reloadAndFilter(); break;
        case 18: _t->activateProject(); break;
        case 19: _t->closeProject(); break;
        case 20: _t->editProjectProperties(); break;
        case 21: _t->editDiagramProperties(); break;
        case 22: _t->newDiagram(); break;
        case 23: _t->insertDiagramAbove(); break;
        case 24: _t->insertDiagramBelow(); break;
        case 25: _t->deleteDiagram(); break;
        case 26: _t->duplicateDiagram(); break;
        case 27: _t->moveDiagramUp(); break;
        case 28: _t->moveDiagramDown(); break;
        case 29: _t->moveDiagramUpTop(); break;
        case 30: _t->moveDiagramUpx10(); break;
        case 31: _t->moveDiagramUpx100(); break;
        case 32: _t->moveDiagramDownx10(); break;
        case 33: _t->moveDiagramDownx100(); break;
        case 34: _t->addTitleBlockTemplate(); break;
        case 35: _t->editTitleBlockTemplate(); break;
        case 36: _t->removeTitleBlockTemplate(); break;
        case 37: _t->updateButtons(); break;
        case 38: _t->handleContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 39: _t->filterEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ElementsPanelWidget::*)(QETProject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForProject)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(QETProject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForNewDiagram)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(QETProject * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForNewDiagramAt)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(QETProject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForProjectClosing)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(QETProject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForProjectPropertiesEdition)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(Diagram * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramPropertiesEdition)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(Diagram * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramDeletion)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramsDeletion)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveUp)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveDown)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveUpTop)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveUpx10)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveUpx100)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveDownx10)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ElementsPanelWidget::*)(const QList<Diagram*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanelWidget::requestForDiagramMoveDownx100)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ElementsPanelWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ElementsPanelWidget.data,
    qt_meta_data_ElementsPanelWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementsPanelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementsPanelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementsPanelWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ElementsPanelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void ElementsPanelWidget::requestForProject(QETProject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ElementsPanelWidget::requestForNewDiagram(QETProject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ElementsPanelWidget::requestForNewDiagramAt(QETProject * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ElementsPanelWidget::requestForProjectClosing(QETProject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ElementsPanelWidget::requestForProjectPropertiesEdition(QETProject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ElementsPanelWidget::requestForDiagramPropertiesEdition(Diagram * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ElementsPanelWidget::requestForDiagramDeletion(Diagram * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ElementsPanelWidget::requestForDiagramsDeletion(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ElementsPanelWidget::requestForDiagramMoveUp(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ElementsPanelWidget::requestForDiagramMoveDown(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ElementsPanelWidget::requestForDiagramMoveUpTop(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ElementsPanelWidget::requestForDiagramMoveUpx10(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ElementsPanelWidget::requestForDiagramMoveUpx100(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ElementsPanelWidget::requestForDiagramMoveDownx10(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ElementsPanelWidget::requestForDiagramMoveDownx100(const QList<Diagram*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
