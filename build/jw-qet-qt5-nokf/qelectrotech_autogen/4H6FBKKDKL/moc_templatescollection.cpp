/****************************************************************************
** Meta object code from reading C++ file 'templatescollection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/titleblock/templatescollection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templatescollection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TitleBlockTemplatesCollection_t {
    QByteArrayData data[5];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TitleBlockTemplatesCollection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TitleBlockTemplatesCollection_t qt_meta_stringdata_TitleBlockTemplatesCollection = {
    {
QT_MOC_LITERAL(0, 0, 29), // "TitleBlockTemplatesCollection"
QT_MOC_LITERAL(1, 30, 7), // "changed"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 30), // "TitleBlockTemplatesCollection*"
QT_MOC_LITERAL(4, 70, 13) // "aboutToRemove"

    },
    "TitleBlockTemplatesCollection\0changed\0"
    "\0TitleBlockTemplatesCollection*\0"
    "aboutToRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TitleBlockTemplatesCollection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       1,    1,   34,    2, 0x26 /* Public | MethodCloned */,
       4,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,

       0        // eod
};

void TitleBlockTemplatesCollection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TitleBlockTemplatesCollection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< TitleBlockTemplatesCollection*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->changed((*reinterpret_cast< TitleBlockTemplatesCollection*(*)>(_a[1]))); break;
        case 2: _t->aboutToRemove((*reinterpret_cast< TitleBlockTemplatesCollection*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TitleBlockTemplatesCollection* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TitleBlockTemplatesCollection* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TitleBlockTemplatesCollection* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TitleBlockTemplatesCollection::*)(TitleBlockTemplatesCollection * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBlockTemplatesCollection::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TitleBlockTemplatesCollection::*)(TitleBlockTemplatesCollection * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBlockTemplatesCollection::aboutToRemove)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TitleBlockTemplatesCollection::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TitleBlockTemplatesCollection.data,
    qt_meta_data_TitleBlockTemplatesCollection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TitleBlockTemplatesCollection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TitleBlockTemplatesCollection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TitleBlockTemplatesCollection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TitleBlockTemplatesCollection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TitleBlockTemplatesCollection::changed(TitleBlockTemplatesCollection * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void TitleBlockTemplatesCollection::aboutToRemove(TitleBlockTemplatesCollection * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_TitleBlockTemplatesProjectCollection_t {
    QByteArrayData data[1];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TitleBlockTemplatesProjectCollection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TitleBlockTemplatesProjectCollection_t qt_meta_stringdata_TitleBlockTemplatesProjectCollection = {
    {
QT_MOC_LITERAL(0, 0, 36) // "TitleBlockTemplatesProjectCol..."

    },
    "TitleBlockTemplatesProjectCollection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TitleBlockTemplatesProjectCollection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TitleBlockTemplatesProjectCollection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject TitleBlockTemplatesProjectCollection::staticMetaObject = { {
    QMetaObject::SuperData::link<TitleBlockTemplatesCollection::staticMetaObject>(),
    qt_meta_stringdata_TitleBlockTemplatesProjectCollection.data,
    qt_meta_data_TitleBlockTemplatesProjectCollection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TitleBlockTemplatesProjectCollection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TitleBlockTemplatesProjectCollection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TitleBlockTemplatesProjectCollection.stringdata0))
        return static_cast<void*>(this);
    return TitleBlockTemplatesCollection::qt_metacast(_clname);
}

int TitleBlockTemplatesProjectCollection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TitleBlockTemplatesCollection::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TitleBlockTemplatesFilesCollection_t {
    QByteArrayData data[4];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TitleBlockTemplatesFilesCollection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TitleBlockTemplatesFilesCollection_t qt_meta_stringdata_TitleBlockTemplatesFilesCollection = {
    {
QT_MOC_LITERAL(0, 0, 34), // "TitleBlockTemplatesFilesColle..."
QT_MOC_LITERAL(1, 35, 17), // "fileSystemChanged"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 3) // "str"

    },
    "TitleBlockTemplatesFilesCollection\0"
    "fileSystemChanged\0\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TitleBlockTemplatesFilesCollection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void TitleBlockTemplatesFilesCollection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TitleBlockTemplatesFilesCollection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileSystemChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TitleBlockTemplatesFilesCollection::staticMetaObject = { {
    QMetaObject::SuperData::link<TitleBlockTemplatesCollection::staticMetaObject>(),
    qt_meta_stringdata_TitleBlockTemplatesFilesCollection.data,
    qt_meta_data_TitleBlockTemplatesFilesCollection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TitleBlockTemplatesFilesCollection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TitleBlockTemplatesFilesCollection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TitleBlockTemplatesFilesCollection.stringdata0))
        return static_cast<void*>(this);
    return TitleBlockTemplatesCollection::qt_metacast(_clname);
}

int TitleBlockTemplatesFilesCollection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TitleBlockTemplatesCollection::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
