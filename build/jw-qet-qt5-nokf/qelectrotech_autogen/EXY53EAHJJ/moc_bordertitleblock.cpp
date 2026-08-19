/****************************************************************************
** Meta object code from reading C++ file 'bordertitleblock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/bordertitleblock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bordertitleblock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BorderTitleBlock_t {
    QByteArrayData data[17];
    char stringdata0[285];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BorderTitleBlock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BorderTitleBlock_t qt_meta_stringdata_BorderTitleBlock = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BorderTitleBlock"
QT_MOC_LITERAL(1, 17, 13), // "borderChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "old_border"
QT_MOC_LITERAL(4, 43, 10), // "new_border"
QT_MOC_LITERAL(5, 54, 14), // "displayChanged"
QT_MOC_LITERAL(6, 69, 22), // "titleBlockFolioChanged"
QT_MOC_LITERAL(7, 92, 13), // "needFolioData"
QT_MOC_LITERAL(8, 106, 22), // "needTitleBlockTemplate"
QT_MOC_LITERAL(9, 129, 18), // "informationChanged"
QT_MOC_LITERAL(10, 148, 25), // "titleBlockTemplateChanged"
QT_MOC_LITERAL(11, 174, 25), // "titleBlockTemplateRemoved"
QT_MOC_LITERAL(12, 200, 25), // "const TitleBlockTemplate*"
QT_MOC_LITERAL(13, 226, 17), // "displayTitleBlock"
QT_MOC_LITERAL(14, 244, 14), // "displayColumns"
QT_MOC_LITERAL(15, 259, 11), // "displayRows"
QT_MOC_LITERAL(16, 271, 13) // "displayBorder"

    },
    "BorderTitleBlock\0borderChanged\0\0"
    "old_border\0new_border\0displayChanged\0"
    "titleBlockFolioChanged\0needFolioData\0"
    "needTitleBlockTemplate\0informationChanged\0"
    "titleBlockTemplateChanged\0"
    "titleBlockTemplateRemoved\0"
    "const TitleBlockTemplate*\0displayTitleBlock\0"
    "displayColumns\0displayRows\0displayBorder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BorderTitleBlock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    0,   84,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       7,    0,   88,    2, 0x06 /* Public */,
       8,    1,   89,    2, 0x06 /* Public */,
       9,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   93,    2, 0x0a /* Public */,
      11,    2,   96,    2, 0x0a /* Public */,
      11,    1,  101,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  104,    2, 0x0a /* Public */,
      14,    1,  107,    2, 0x0a /* Public */,
      15,    1,  110,    2, 0x0a /* Public */,
      16,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRectF, QMetaType::QRectF,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void BorderTitleBlock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BorderTitleBlock *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->borderChanged((*reinterpret_cast< QRectF(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 1: _t->displayChanged(); break;
        case 2: _t->titleBlockFolioChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->needFolioData(); break;
        case 4: _t->needTitleBlockTemplate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->informationChanged(); break;
        case 6: _t->titleBlockTemplateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->titleBlockTemplateRemoved((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const TitleBlockTemplate*(*)>(_a[2]))); break;
        case 8: _t->titleBlockTemplateRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->displayTitleBlock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->displayColumns((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->displayRows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->displayBorder((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BorderTitleBlock::*)(QRectF , QRectF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::borderChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BorderTitleBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::displayChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BorderTitleBlock::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::titleBlockFolioChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BorderTitleBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::needFolioData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BorderTitleBlock::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::needTitleBlockTemplate)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BorderTitleBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BorderTitleBlock::informationChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BorderTitleBlock::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BorderTitleBlock.data,
    qt_meta_data_BorderTitleBlock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BorderTitleBlock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BorderTitleBlock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BorderTitleBlock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BorderTitleBlock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void BorderTitleBlock::borderChanged(QRectF _t1, QRectF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BorderTitleBlock::displayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BorderTitleBlock::titleBlockFolioChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BorderTitleBlock::needFolioData()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BorderTitleBlock::needTitleBlockTemplate(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BorderTitleBlock::informationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
