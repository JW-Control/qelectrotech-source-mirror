/****************************************************************************
** Meta object code from reading C++ file 'elementtextitemgroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qetgraphicsitem/elementtextitemgroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementtextitemgroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementTextItemGroup_t {
    QByteArrayData data[18];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementTextItemGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementTextItemGroup_t qt_meta_stringdata_ElementTextItemGroup = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ElementTextItemGroup"
QT_MOC_LITERAL(1, 21, 15), // "rotationChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 25), // "verticalAdjustmentChanged"
QT_MOC_LITERAL(4, 64, 16), // "alignmentChanged"
QT_MOC_LITERAL(5, 81, 13), // "Qt::Alignment"
QT_MOC_LITERAL(6, 95, 11), // "nameChanged"
QT_MOC_LITERAL(7, 107, 23), // "holdToBottomPageChanged"
QT_MOC_LITERAL(8, 131, 8), // "xChanged"
QT_MOC_LITERAL(9, 140, 8), // "yChanged"
QT_MOC_LITERAL(10, 149, 12), // "frameChanged"
QT_MOC_LITERAL(11, 162, 5), // "frame"
QT_MOC_LITERAL(12, 168, 3), // "pos"
QT_MOC_LITERAL(13, 172, 8), // "rotation"
QT_MOC_LITERAL(14, 181, 18), // "verticalAdjustment"
QT_MOC_LITERAL(15, 200, 9), // "alignment"
QT_MOC_LITERAL(16, 210, 4), // "name"
QT_MOC_LITERAL(17, 215, 16) // "holdToBottomPage"

    },
    "ElementTextItemGroup\0rotationChanged\0"
    "\0verticalAdjustmentChanged\0alignmentChanged\0"
    "Qt::Alignment\0nameChanged\0"
    "holdToBottomPageChanged\0xChanged\0"
    "yChanged\0frameChanged\0frame\0pos\0"
    "rotation\0verticalAdjustment\0alignment\0"
    "name\0holdToBottomPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementTextItemGroup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       7,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    1,   60,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,
       8,    0,   69,    2, 0x06 /* Public */,
       9,    0,   70,    2, 0x06 /* Public */,
      10,    1,   71,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,

 // properties: name, type, flags
      12, QMetaType::QPointF, 0x00095103,
      13, QMetaType::QReal, 0x00495103,
      14, QMetaType::Int, 0x00495103,
      15, 0x80000000 | 5, 0x0049510b,
      16, QMetaType::QString, 0x00495103,
      17, QMetaType::Bool, 0x00495103,
      11, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       0,
       1,
       2,
       3,
       4,
       7,

       0        // eod
};

void ElementTextItemGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementTextItemGroup *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rotationChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->verticalAdjustmentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->alignmentChanged((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 3: _t->nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->holdToBottomPageChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->xChanged(); break;
        case 6: _t->yChanged(); break;
        case 7: _t->frameChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ElementTextItemGroup::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::rotationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::verticalAdjustmentChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)(Qt::Alignment );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::alignmentChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::nameChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::holdToBottomPageChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::xChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::yChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ElementTextItemGroup::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementTextItemGroup::frameChanged)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ElementTextItemGroup *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->rotation(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->verticalAdjustment(); break;
        case 3: *reinterpret_cast< Qt::Alignment*>(_v) = _t->alignment(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->holdToBottomPage(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->frame(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ElementTextItemGroup *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        case 1: _t->setRotation(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setVerticalAdjustment(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 4: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setHoldToBottomPage(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setFrame(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ElementTextItemGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ElementTextItemGroup.data,
    qt_meta_data_ElementTextItemGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementTextItemGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementTextItemGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementTextItemGroup.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItemGroup"))
        return static_cast< QGraphicsItemGroup*>(this);
    return QObject::qt_metacast(_clname);
}

int ElementTextItemGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ElementTextItemGroup::rotationChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ElementTextItemGroup::verticalAdjustmentChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ElementTextItemGroup::alignmentChanged(Qt::Alignment _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ElementTextItemGroup::nameChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ElementTextItemGroup::holdToBottomPageChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ElementTextItemGroup::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ElementTextItemGroup::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ElementTextItemGroup::frameChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
