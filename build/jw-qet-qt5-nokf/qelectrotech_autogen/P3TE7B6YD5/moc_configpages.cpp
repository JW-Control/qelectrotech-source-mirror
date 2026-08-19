/****************************************************************************
** Meta object code from reading C++ file 'configpages.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/configpage/configpages.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configpages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NewDiagramPage_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewDiagramPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewDiagramPage_t qt_meta_stringdata_NewDiagramPage = {
    {
QT_MOC_LITERAL(0, 0, 14), // "NewDiagramPage"
QT_MOC_LITERAL(1, 15, 20), // "changeToAutoFolioTab"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "setFolioAutonum"
QT_MOC_LITERAL(4, 53, 14), // "saveCurrentTbp"
QT_MOC_LITERAL(5, 68, 12) // "loadSavedTbp"

    },
    "NewDiagramPage\0changeToAutoFolioTab\0"
    "\0setFolioAutonum\0saveCurrentTbp\0"
    "loadSavedTbp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewDiagramPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       4,    0,   38,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NewDiagramPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NewDiagramPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changeToAutoFolioTab(); break;
        case 1: _t->setFolioAutonum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->saveCurrentTbp(); break;
        case 3: _t->loadSavedTbp(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NewDiagramPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ConfigPage::staticMetaObject>(),
    qt_meta_stringdata_NewDiagramPage.data,
    qt_meta_data_NewDiagramPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NewDiagramPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewDiagramPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewDiagramPage.stringdata0))
        return static_cast<void*>(this);
    return ConfigPage::qt_metacast(_clname);
}

int NewDiagramPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConfigPage::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_ExportConfigPage_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExportConfigPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExportConfigPage_t qt_meta_stringdata_ExportConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 16) // "ExportConfigPage"

    },
    "ExportConfigPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExportConfigPage[] = {

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

void ExportConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ExportConfigPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ConfigPage::staticMetaObject>(),
    qt_meta_stringdata_ExportConfigPage.data,
    qt_meta_data_ExportConfigPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExportConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExportConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExportConfigPage.stringdata0))
        return static_cast<void*>(this);
    return ConfigPage::qt_metacast(_clname);
}

int ExportConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConfigPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PrintConfigPage_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrintConfigPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrintConfigPage_t qt_meta_stringdata_PrintConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 15) // "PrintConfigPage"

    },
    "PrintConfigPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrintConfigPage[] = {

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

void PrintConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject PrintConfigPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ConfigPage::staticMetaObject>(),
    qt_meta_stringdata_PrintConfigPage.data,
    qt_meta_data_PrintConfigPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrintConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrintConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrintConfigPage.stringdata0))
        return static_cast<void*>(this);
    return ConfigPage::qt_metacast(_clname);
}

int PrintConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConfigPage::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
