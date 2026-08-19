/****************************************************************************
** Meta object code from reading C++ file 'parttext.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/graphicspart/parttext.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parttext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PartText_t {
    QByteArrayData data[16];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PartText_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PartText_t qt_meta_stringdata_PartText = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PartText"
QT_MOC_LITERAL(1, 9, 11), // "fontChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "font"
QT_MOC_LITERAL(4, 27, 12), // "colorChanged"
QT_MOC_LITERAL(5, 40, 5), // "color"
QT_MOC_LITERAL(6, 46, 16), // "plainTextChanged"
QT_MOC_LITERAL(7, 63, 4), // "text"
QT_MOC_LITERAL(8, 68, 16), // "alignmentChanged"
QT_MOC_LITERAL(9, 85, 13), // "Qt::Alignment"
QT_MOC_LITERAL(10, 99, 9), // "alignment"
QT_MOC_LITERAL(11, 109, 18), // "adjustItemPosition"
QT_MOC_LITERAL(12, 128, 11), // "setEditable"
QT_MOC_LITERAL(13, 140, 12), // "startEdition"
QT_MOC_LITERAL(14, 153, 10), // "endEdition"
QT_MOC_LITERAL(15, 164, 9) // "real_size"

    },
    "PartText\0fontChanged\0\0font\0colorChanged\0"
    "color\0plainTextChanged\0text\0"
    "alignmentChanged\0Qt::Alignment\0alignment\0"
    "adjustItemPosition\0setEditable\0"
    "startEdition\0endEdition\0real_size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PartText[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       5,   80, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   71,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x2a /* Public | MethodCloned */,
      12,    1,   75,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x0a /* Public */,
      14,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QFont,    3,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      15, QMetaType::QReal, 0x00095003,
       5, QMetaType::QColor, 0x00495003,
       7, QMetaType::QString, 0x00495003,
       3, QMetaType::QFont, 0x00495103,
      10, 0x80000000 | 9, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,
       2,
       0,
       3,

       0        // eod
};

void PartText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PartText *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 1: _t->colorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->plainTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->alignmentChanged((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 4: _t->adjustItemPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->adjustItemPosition(); break;
        case 6: _t->setEditable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->startEdition(); break;
        case 8: _t->endEdition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PartText::*)(const QFont & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartText::fontChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PartText::*)(const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartText::colorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PartText::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartText::plainTextChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PartText::*)(Qt::Alignment );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartText::alignmentChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PartText *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->realSize(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->defaultTextColor(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->toPlainText(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 4: *reinterpret_cast< Qt::Alignment*>(_v) = _t->alignment(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PartText *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRealSize(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setDefaultTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setPlainText(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: _t->setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PartText::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsTextItem::staticMetaObject>(),
    qt_meta_stringdata_PartText.data,
    qt_meta_data_PartText,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PartText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartText::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PartText.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CustomElementPart"))
        return static_cast< CustomElementPart*>(this);
    return QGraphicsTextItem::qt_metacast(_clname);
}

int PartText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsTextItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
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
void PartText::fontChanged(const QFont & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PartText::colorChanged(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PartText::plainTextChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PartText::alignmentChanged(Qt::Alignment _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
