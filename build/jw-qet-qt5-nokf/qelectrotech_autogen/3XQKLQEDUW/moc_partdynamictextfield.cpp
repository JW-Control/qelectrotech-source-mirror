/****************************************************************************
** Meta object code from reading C++ file 'partdynamictextfield.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/graphicspart/partdynamictextfield.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'partdynamictextfield.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PartDynamicTextField_t {
    QByteArrayData data[33];
    char stringdata0[422];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PartDynamicTextField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PartDynamicTextField_t qt_meta_stringdata_PartDynamicTextField = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PartDynamicTextField"
QT_MOC_LITERAL(1, 21, 11), // "taggChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "tagg"
QT_MOC_LITERAL(4, 39, 11), // "textChanged"
QT_MOC_LITERAL(5, 51, 4), // "text"
QT_MOC_LITERAL(6, 56, 15), // "textFromChanged"
QT_MOC_LITERAL(7, 72, 32), // "DynamicElementTextItem::TextFrom"
QT_MOC_LITERAL(8, 105, 9), // "text_from"
QT_MOC_LITERAL(9, 115, 15), // "infoNameChanged"
QT_MOC_LITERAL(10, 131, 4), // "info"
QT_MOC_LITERAL(11, 136, 20), // "compositeTextChanged"
QT_MOC_LITERAL(12, 157, 12), // "colorChanged"
QT_MOC_LITERAL(13, 170, 5), // "color"
QT_MOC_LITERAL(14, 176, 12), // "frameChanged"
QT_MOC_LITERAL(15, 189, 5), // "frame"
QT_MOC_LITERAL(16, 195, 16), // "textWidthChanged"
QT_MOC_LITERAL(17, 212, 5), // "width"
QT_MOC_LITERAL(18, 218, 16), // "alignmentChanged"
QT_MOC_LITERAL(19, 235, 13), // "Qt::Alignment"
QT_MOC_LITERAL(20, 249, 9), // "alignment"
QT_MOC_LITERAL(21, 259, 11), // "fontChanged"
QT_MOC_LITERAL(22, 271, 4), // "font"
QT_MOC_LITERAL(23, 276, 25), // "keepVisualRotationChanged"
QT_MOC_LITERAL(24, 302, 4), // "keep"
QT_MOC_LITERAL(25, 307, 26), // "rotationPointCenterChanged"
QT_MOC_LITERAL(26, 334, 6), // "center"
QT_MOC_LITERAL(27, 341, 8), // "textFrom"
QT_MOC_LITERAL(28, 350, 8), // "infoName"
QT_MOC_LITERAL(29, 359, 13), // "compositeText"
QT_MOC_LITERAL(30, 373, 9), // "textWidth"
QT_MOC_LITERAL(31, 383, 18), // "keepVisualRotation"
QT_MOC_LITERAL(32, 402, 19) // "rotationPointCenter"

    },
    "PartDynamicTextField\0taggChanged\0\0"
    "tagg\0textChanged\0text\0textFromChanged\0"
    "DynamicElementTextItem::TextFrom\0"
    "text_from\0infoNameChanged\0info\0"
    "compositeTextChanged\0colorChanged\0"
    "color\0frameChanged\0frame\0textWidthChanged\0"
    "width\0alignmentChanged\0Qt::Alignment\0"
    "alignment\0fontChanged\0font\0"
    "keepVisualRotationChanged\0keep\0"
    "rotationPointCenterChanged\0center\0"
    "textFrom\0infoName\0compositeText\0"
    "textWidth\0keepVisualRotation\0"
    "rotationPointCenter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PartDynamicTextField[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
      11,  110, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       9,    1,   83,    2, 0x06 /* Public */,
      11,    1,   86,    2, 0x06 /* Public */,
      12,    1,   89,    2, 0x06 /* Public */,
      14,    1,   92,    2, 0x06 /* Public */,
      16,    1,   95,    2, 0x06 /* Public */,
      18,    1,   98,    2, 0x06 /* Public */,
      21,    1,  101,    2, 0x06 /* Public */,
      23,    1,  104,    2, 0x06 /* Public */,
      25,    1,  107,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QReal,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QFont,   22,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   26,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00495103,
      27, 0x80000000 | 7, 0x0049510b,
      28, QMetaType::QString, 0x00495103,
      29, QMetaType::QString, 0x00495103,
      13, QMetaType::QColor, 0x00495103,
      15, QMetaType::Bool, 0x00495103,
      30, QMetaType::QReal, 0x00495103,
      20, 0x80000000 | 19, 0x0049510b,
      22, QMetaType::QFont, 0x00495103,
      31, QMetaType::Bool, 0x00495103,
      32, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      11,

       0        // eod
};

void PartDynamicTextField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PartDynamicTextField *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->taggChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->textFromChanged((*reinterpret_cast< DynamicElementTextItem::TextFrom(*)>(_a[1]))); break;
        case 3: _t->infoNameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->compositeTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 6: _t->frameChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->textWidthChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 8: _t->alignmentChanged((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 9: _t->fontChanged((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 10: _t->keepVisualRotationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->rotationPointCenterChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PartDynamicTextField::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::taggChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::textChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(DynamicElementTextItem::TextFrom );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::textFromChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::infoNameChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::compositeTextChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::colorChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::frameChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::textWidthChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(Qt::Alignment );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::alignmentChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(QFont );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::fontChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::keepVisualRotationChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PartDynamicTextField::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PartDynamicTextField::rotationPointCenterChanged)) {
                *result = 11;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PartDynamicTextField *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< DynamicElementTextItem::TextFrom*>(_v) = _t->textFrom(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->infoName(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->compositeText(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->frame(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->textWidth(); break;
        case 7: *reinterpret_cast< Qt::Alignment*>(_v) = _t->alignment(); break;
        case 8: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->keepVisualRotation(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->rotationPointCenter(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PartDynamicTextField *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTextFrom(*reinterpret_cast< DynamicElementTextItem::TextFrom*>(_v)); break;
        case 2: _t->setInfoName(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setCompositeText(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setFrame(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setTextWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 8: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 9: _t->setKeepVisualRotation(*reinterpret_cast< bool*>(_v)); break;
        case 10: _t->setRotationPointCenter(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

static const QMetaObject::SuperData qt_meta_extradata_PartDynamicTextField[] = {
    QMetaObject::SuperData::link<DynamicElementTextItem::staticMetaObject>(),
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject PartDynamicTextField::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsTextItem::staticMetaObject>(),
    qt_meta_stringdata_PartDynamicTextField.data,
    qt_meta_data_PartDynamicTextField,
    qt_static_metacall,
    qt_meta_extradata_PartDynamicTextField,
    nullptr
} };


const QMetaObject *PartDynamicTextField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDynamicTextField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PartDynamicTextField.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CustomElementPart"))
        return static_cast< CustomElementPart*>(this);
    return QGraphicsTextItem::qt_metacast(_clname);
}

int PartDynamicTextField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsTextItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PartDynamicTextField::taggChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PartDynamicTextField::textChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PartDynamicTextField::textFromChanged(DynamicElementTextItem::TextFrom _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PartDynamicTextField::infoNameChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PartDynamicTextField::compositeTextChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PartDynamicTextField::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PartDynamicTextField::frameChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PartDynamicTextField::textWidthChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PartDynamicTextField::alignmentChanged(Qt::Alignment _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PartDynamicTextField::fontChanged(QFont _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PartDynamicTextField::keepVisualRotationChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PartDynamicTextField::rotationPointCenterChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
