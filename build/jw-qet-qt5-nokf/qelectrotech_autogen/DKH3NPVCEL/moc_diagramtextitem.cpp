/****************************************************************************
** Meta object code from reading C++ file 'diagramtextitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qetgraphicsitem/diagramtextitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diagramtextitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DiagramTextItem_t {
    QByteArrayData data[13];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DiagramTextItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DiagramTextItem_t qt_meta_stringdata_DiagramTextItem = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DiagramTextItem"
QT_MOC_LITERAL(1, 16, 12), // "colorChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "color"
QT_MOC_LITERAL(4, 36, 16), // "alignmentChanged"
QT_MOC_LITERAL(5, 53, 13), // "Qt::Alignment"
QT_MOC_LITERAL(6, 67, 9), // "alignment"
QT_MOC_LITERAL(7, 77, 10), // "textEdited"
QT_MOC_LITERAL(8, 88, 7), // "old_str"
QT_MOC_LITERAL(9, 96, 7), // "new_str"
QT_MOC_LITERAL(10, 104, 11), // "fontChanged"
QT_MOC_LITERAL(11, 116, 4), // "font"
QT_MOC_LITERAL(12, 121, 9) // "plainText"

    },
    "DiagramTextItem\0colorChanged\0\0color\0"
    "alignmentChanged\0Qt::Alignment\0alignment\0"
    "textEdited\0old_str\0new_str\0fontChanged\0"
    "font\0plainText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DiagramTextItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       7,    2,   40,    2, 0x06 /* Public */,
      10,    1,   45,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QFont,   11,

 // properties: name, type, flags
       3, QMetaType::QColor, 0x00495103,
       6, 0x80000000 | 5, 0x0049510b,
      12, QMetaType::QString, 0x00095103,
      11, QMetaType::QFont, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       0,
       3,

       0        // eod
};

void DiagramTextItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DiagramTextItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->alignmentChanged((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 2: _t->textEdited((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->fontChanged((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DiagramTextItem::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DiagramTextItem::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DiagramTextItem::*)(Qt::Alignment );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DiagramTextItem::alignmentChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DiagramTextItem::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DiagramTextItem::textEdited)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DiagramTextItem::*)(QFont );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DiagramTextItem::fontChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DiagramTextItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 1: *reinterpret_cast< Qt::Alignment*>(_v) = _t->alignment(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->toPlainText(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DiagramTextItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 2: _t->setPlainText(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DiagramTextItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsTextItem::staticMetaObject>(),
    qt_meta_stringdata_DiagramTextItem.data,
    qt_meta_data_DiagramTextItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DiagramTextItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DiagramTextItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DiagramTextItem.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsTextItem::qt_metacast(_clname);
}

int DiagramTextItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsTextItem::qt_metacall(_c, _id, _a);
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
void DiagramTextItem::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DiagramTextItem::alignmentChanged(Qt::Alignment _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DiagramTextItem::textEdited(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DiagramTextItem::fontChanged(QFont _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
