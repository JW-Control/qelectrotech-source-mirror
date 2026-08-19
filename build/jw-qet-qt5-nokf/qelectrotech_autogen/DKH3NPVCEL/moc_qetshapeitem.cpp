/****************************************************************************
** Meta object code from reading C++ file 'qetshapeitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qetgraphicsitem/qetshapeitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qetshapeitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QetShapeItem_t {
    QByteArrayData data[20];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QetShapeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QetShapeItem_t qt_meta_stringdata_QetShapeItem = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QetShapeItem"
QT_MOC_LITERAL(1, 13, 10), // "penChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "brushChanged"
QT_MOC_LITERAL(4, 38, 12), // "closeChanged"
QT_MOC_LITERAL(5, 51, 14), // "XRadiusChanged"
QT_MOC_LITERAL(6, 66, 14), // "YRadiusChanged"
QT_MOC_LITERAL(7, 81, 3), // "pen"
QT_MOC_LITERAL(8, 85, 5), // "brush"
QT_MOC_LITERAL(9, 91, 4), // "rect"
QT_MOC_LITERAL(10, 96, 4), // "line"
QT_MOC_LITERAL(11, 101, 7), // "polygon"
QT_MOC_LITERAL(12, 109, 5), // "close"
QT_MOC_LITERAL(13, 115, 7), // "xRadius"
QT_MOC_LITERAL(14, 123, 7), // "yRadius"
QT_MOC_LITERAL(15, 131, 9), // "ShapeType"
QT_MOC_LITERAL(16, 141, 4), // "Line"
QT_MOC_LITERAL(17, 146, 9), // "Rectangle"
QT_MOC_LITERAL(18, 156, 7), // "Ellipse"
QT_MOC_LITERAL(19, 164, 7) // "Polygon"

    },
    "QetShapeItem\0penChanged\0\0brushChanged\0"
    "closeChanged\0XRadiusChanged\0YRadiusChanged\0"
    "pen\0brush\0rect\0line\0polygon\0close\0"
    "xRadius\0yRadius\0ShapeType\0Line\0Rectangle\0"
    "Ellipse\0Polygon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QetShapeItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       8,   44, // properties
       1,   76, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QPen, 0x00495103,
       8, QMetaType::QBrush, 0x00495103,
       9, QMetaType::QRectF, 0x00095103,
      10, QMetaType::QLineF, 0x00095103,
      11, QMetaType::QPolygonF, 0x00095103,
      12, QMetaType::Bool, 0x00495003,
      13, QMetaType::QReal, 0x00495103,
      14, QMetaType::QReal, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       0,
       0,
       0,
       2,
       3,
       4,

 // enums: name, alias, flags, count, data
      15,   15, 0x0,    4,   81,

 // enum data: key, value
      16, uint(QetShapeItem::Line),
      17, uint(QetShapeItem::Rectangle),
      18, uint(QetShapeItem::Ellipse),
      19, uint(QetShapeItem::Polygon),

       0        // eod
};

void QetShapeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QetShapeItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->penChanged(); break;
        case 1: _t->brushChanged(); break;
        case 2: _t->closeChanged(); break;
        case 3: _t->XRadiusChanged(); break;
        case 4: _t->YRadiusChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QetShapeItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QetShapeItem::penChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QetShapeItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QetShapeItem::brushChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QetShapeItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QetShapeItem::closeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QetShapeItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QetShapeItem::XRadiusChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QetShapeItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QetShapeItem::YRadiusChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QetShapeItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 2: *reinterpret_cast< QRectF*>(_v) = _t->rect(); break;
        case 3: *reinterpret_cast< QLineF*>(_v) = _t->line(); break;
        case 4: *reinterpret_cast< QPolygonF*>(_v) = _t->polygon(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isClosed(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->XRadius(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->YRadius(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QetShapeItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 2: _t->setRect(*reinterpret_cast< QRectF*>(_v)); break;
        case 3: _t->setLine(*reinterpret_cast< QLineF*>(_v)); break;
        case 4: _t->setPolygon(*reinterpret_cast< QPolygonF*>(_v)); break;
        case 5: _t->setClosed(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setXRadius(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setYRadius(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject QetShapeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QetGraphicsItem::staticMetaObject>(),
    qt_meta_stringdata_QetShapeItem.data,
    qt_meta_data_QetShapeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QetShapeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QetShapeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QetShapeItem.stringdata0))
        return static_cast<void*>(this);
    return QetGraphicsItem::qt_metacast(_clname);
}

int QetShapeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QetGraphicsItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QetShapeItem::penChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QetShapeItem::brushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QetShapeItem::closeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QetShapeItem::XRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QetShapeItem::YRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
