/****************************************************************************
** Meta object code from reading C++ file 'elementscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/elementscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementScene_t {
    QByteArrayData data[23];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementScene_t qt_meta_stringdata_ElementScene = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ElementScene"
QT_MOC_LITERAL(1, 13, 10), // "partsAdded"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "partsRemoved"
QT_MOC_LITERAL(4, 38, 18), // "partsZValueChanged"
QT_MOC_LITERAL(5, 57, 16), // "pasteAreaDefined"
QT_MOC_LITERAL(6, 74, 11), // "needZoomFit"
QT_MOC_LITERAL(7, 86, 18), // "elementInfoChanged"
QT_MOC_LITERAL(8, 105, 18), // "elementTypeChanged"
QT_MOC_LITERAL(9, 124, 10), // "mouseMoved"
QT_MOC_LITERAL(10, 135, 3), // "pos"
QT_MOC_LITERAL(11, 139, 11), // "slot_select"
QT_MOC_LITERAL(12, 151, 14), // "ElementContent"
QT_MOC_LITERAL(13, 166, 14), // "slot_selectAll"
QT_MOC_LITERAL(14, 181, 16), // "slot_deselectAll"
QT_MOC_LITERAL(15, 198, 20), // "slot_invertSelection"
QT_MOC_LITERAL(16, 219, 11), // "slot_delete"
QT_MOC_LITERAL(17, 231, 14), // "slot_editNames"
QT_MOC_LITERAL(18, 246, 27), // "slot_editAuthorInformations"
QT_MOC_LITERAL(19, 274, 19), // "slot_editProperties"
QT_MOC_LITERAL(20, 294, 22), // "managePrimitivesGroups"
QT_MOC_LITERAL(21, 317, 11), // "stackAction"
QT_MOC_LITERAL(22, 329, 22) // "ElementEditionCommand*"

    },
    "ElementScene\0partsAdded\0\0partsRemoved\0"
    "partsZValueChanged\0pasteAreaDefined\0"
    "needZoomFit\0elementInfoChanged\0"
    "elementTypeChanged\0mouseMoved\0pos\0"
    "slot_select\0ElementContent\0slot_selectAll\0"
    "slot_deselectAll\0slot_invertSelection\0"
    "slot_delete\0slot_editNames\0"
    "slot_editAuthorInformations\0"
    "slot_editProperties\0managePrimitivesGroups\0"
    "stackAction\0ElementEditionCommand*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       4,    0,  106,    2, 0x06 /* Public */,
       5,    1,  107,    2, 0x06 /* Public */,
       6,    0,  110,    2, 0x06 /* Public */,
       7,    0,  111,    2, 0x06 /* Public */,
       8,    0,  112,    2, 0x06 /* Public */,
       9,    1,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  116,    2, 0x0a /* Public */,
      13,    0,  119,    2, 0x0a /* Public */,
      14,    0,  120,    2, 0x0a /* Public */,
      15,    0,  121,    2, 0x0a /* Public */,
      16,    0,  122,    2, 0x0a /* Public */,
      17,    0,  123,    2, 0x0a /* Public */,
      18,    0,  124,    2, 0x0a /* Public */,
      19,    0,  125,    2, 0x0a /* Public */,
      20,    0,  126,    2, 0x0a /* Public */,
      21,    1,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRectF,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,    2,

       0        // eod
};

void ElementScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->partsAdded(); break;
        case 1: _t->partsRemoved(); break;
        case 2: _t->partsZValueChanged(); break;
        case 3: _t->pasteAreaDefined((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 4: _t->needZoomFit(); break;
        case 5: _t->elementInfoChanged(); break;
        case 6: _t->elementTypeChanged(); break;
        case 7: _t->mouseMoved((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 8: _t->slot_select((*reinterpret_cast< const ElementContent(*)>(_a[1]))); break;
        case 9: _t->slot_selectAll(); break;
        case 10: _t->slot_deselectAll(); break;
        case 11: _t->slot_invertSelection(); break;
        case 12: _t->slot_delete(); break;
        case 13: _t->slot_editNames(); break;
        case 14: _t->slot_editAuthorInformations(); break;
        case 15: _t->slot_editProperties(); break;
        case 16: _t->managePrimitivesGroups(); break;
        case 17: _t->stackAction((*reinterpret_cast< ElementEditionCommand*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::partsAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::partsRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::partsZValueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)(const QRectF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::pasteAreaDefined)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::needZoomFit)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::elementInfoChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::elementTypeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ElementScene::*)(const QPointF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementScene::mouseMoved)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ElementScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_ElementScene.data,
    qt_meta_data_ElementScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int ElementScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ElementScene::partsAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ElementScene::partsRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ElementScene::partsZValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ElementScene::pasteAreaDefined(const QRectF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ElementScene::needZoomFit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ElementScene::elementInfoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ElementScene::elementTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ElementScene::mouseMoved(const QPointF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
