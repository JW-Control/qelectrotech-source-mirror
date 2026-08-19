/****************************************************************************
** Meta object code from reading C++ file 'partrectangle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/graphicspart/partrectangle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'partrectangle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PartRectangle_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PartRectangle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PartRectangle_t qt_meta_stringdata_PartRectangle = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PartRectangle"
QT_MOC_LITERAL(1, 14, 11), // "rectChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "XRadiusChanged"
QT_MOC_LITERAL(4, 42, 14), // "YRadiusChanged"
QT_MOC_LITERAL(5, 57, 15), // "rotationChanged"
QT_MOC_LITERAL(6, 73, 4), // "rect"
QT_MOC_LITERAL(7, 78, 7), // "xRadius"
QT_MOC_LITERAL(8, 86, 7), // "yRadius"
QT_MOC_LITERAL(9, 94, 8) // "rotation"

    },
    "PartRectangle\0rectChanged\0\0XRadiusChanged\0"
    "YRadiusChanged\0rotationChanged\0rect\0"
    "xRadius\0yRadius\0rotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PartRectangle[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::QRectF, 0x00095103,
       7, QMetaType::QReal, 0x00495103,
       8, QMetaType::QReal, 0x00495103,
       9, QMetaType::QReal, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void PartRectangle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PartRectangle *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rectChanged(); break;
        case 1: _t->XRadiusChanged(); break;
        case 2: _t->YRadiusChanged(); break;
        case 3: _t->rotationChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PartRectangle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartRectangle::rectChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PartRectangle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartRectangle::XRadiusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PartRectangle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartRectangle::YRadiusChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PartRectangle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartRectangle::rotationChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PartRectangle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QRectF*>(_v) = _t->rect(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->XRadius(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->YRadius(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->rotation(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PartRectangle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRect(*reinterpret_cast< QRectF*>(_v)); break;
        case 1: _t->setXRadius(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setYRadius(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setRotation(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject PartRectangle::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomElementGraphicPart::staticMetaObject>(),
    qt_meta_stringdata_PartRectangle.data,
    qt_meta_data_PartRectangle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PartRectangle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartRectangle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PartRectangle.stringdata0))
        return static_cast<void*>(this);
    return CustomElementGraphicPart::qt_metacast(_clname);
}

int PartRectangle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomElementGraphicPart::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PartRectangle::rectChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PartRectangle::XRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PartRectangle::YRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PartRectangle::rotationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
