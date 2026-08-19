/****************************************************************************
** Meta object code from reading C++ file 'partline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/graphicspart/partline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'partline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PartLine_t {
    QByteArrayData data[13];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PartLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PartLine_t qt_meta_stringdata_PartLine = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PartLine"
QT_MOC_LITERAL(1, 9, 11), // "lineChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 19), // "firstEndTypeChanged"
QT_MOC_LITERAL(4, 42, 20), // "secondEndTypeChanged"
QT_MOC_LITERAL(5, 63, 21), // "firstEndLengthChanged"
QT_MOC_LITERAL(6, 85, 22), // "secondEndLengthChanged"
QT_MOC_LITERAL(7, 108, 4), // "end1"
QT_MOC_LITERAL(8, 113, 12), // "Qet::EndType"
QT_MOC_LITERAL(9, 126, 4), // "end2"
QT_MOC_LITERAL(10, 131, 7), // "length1"
QT_MOC_LITERAL(11, 139, 7), // "length2"
QT_MOC_LITERAL(12, 147, 4) // "line"

    },
    "PartLine\0lineChanged\0\0firstEndTypeChanged\0"
    "secondEndTypeChanged\0firstEndLengthChanged\0"
    "secondEndLengthChanged\0end1\0Qet::EndType\0"
    "end2\0length1\0length2\0line"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PartLine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
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
       7, 0x80000000 | 8, 0x0009500b,
       9, 0x80000000 | 8, 0x0009500b,
      10, QMetaType::QReal, 0x00095003,
      11, QMetaType::QReal, 0x00095003,
      12, QMetaType::QLineF, 0x00095103,

       0        // eod
};

void PartLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PartLine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->lineChanged(); break;
        case 1: _t->firstEndTypeChanged(); break;
        case 2: _t->secondEndTypeChanged(); break;
        case 3: _t->firstEndLengthChanged(); break;
        case 4: _t->secondEndLengthChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PartLine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartLine::lineChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PartLine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartLine::firstEndTypeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PartLine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartLine::secondEndTypeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PartLine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartLine::firstEndLengthChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PartLine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartLine::secondEndLengthChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PartLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Qet::EndType*>(_v) = _t->firstEndType(); break;
        case 1: *reinterpret_cast< Qet::EndType*>(_v) = _t->secondEndType(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->firstEndLength(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->secondEndLength(); break;
        case 4: *reinterpret_cast< QLineF*>(_v) = _t->line(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PartLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFirstEndType(*reinterpret_cast< Qet::EndType*>(_v)); break;
        case 1: _t->setSecondEndType(*reinterpret_cast< Qet::EndType*>(_v)); break;
        case 2: _t->setFirstEndLength(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setSecondEndLength(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setLine(*reinterpret_cast< QLineF*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

static const QMetaObject::SuperData qt_meta_extradata_PartLine[] = {
    QMetaObject::SuperData::link<Qet::staticMetaObject>(),
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject PartLine::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomElementGraphicPart::staticMetaObject>(),
    qt_meta_stringdata_PartLine.data,
    qt_meta_data_PartLine,
    qt_static_metacall,
    qt_meta_extradata_PartLine,
    nullptr
} };


const QMetaObject *PartLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PartLine.stringdata0))
        return static_cast<void*>(this);
    return CustomElementGraphicPart::qt_metacast(_clname);
}

int PartLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomElementGraphicPart::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PartLine::lineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PartLine::firstEndTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PartLine::secondEndTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PartLine::firstEndLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PartLine::secondEndLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
