/****************************************************************************
** Meta object code from reading C++ file 'projectconfigpages.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/configpage/projectconfigpages.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectconfigpages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProjectConfigPage_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectConfigPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectConfigPage_t qt_meta_stringdata_ProjectConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 17) // "ProjectConfigPage"

    },
    "ProjectConfigPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectConfigPage[] = {

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

void ProjectConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ProjectConfigPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ConfigPage::staticMetaObject>(),
    qt_meta_stringdata_ProjectConfigPage.data,
    qt_meta_data_ProjectConfigPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProjectConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectConfigPage.stringdata0))
        return static_cast<void*>(this);
    return ConfigPage::qt_metacast(_clname);
}

int ProjectConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConfigPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ProjectMainConfigPage_t {
    QByteArrayData data[3];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectMainConfigPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectMainConfigPage_t qt_meta_stringdata_ProjectMainConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ProjectMainConfigPage"
QT_MOC_LITERAL(1, 22, 17), // "resetUsageTracker"
QT_MOC_LITERAL(2, 40, 0) // ""

    },
    "ProjectMainConfigPage\0resetUsageTracker\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectMainConfigPage[] = {

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
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ProjectMainConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProjectMainConfigPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resetUsageTracker(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ProjectMainConfigPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ProjectConfigPage::staticMetaObject>(),
    qt_meta_stringdata_ProjectMainConfigPage.data,
    qt_meta_data_ProjectMainConfigPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProjectMainConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectMainConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectMainConfigPage.stringdata0))
        return static_cast<void*>(this);
    return ProjectConfigPage::qt_metacast(_clname);
}

int ProjectMainConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProjectConfigPage::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ProjectAutoNumConfigPage_t {
    QByteArrayData data[16];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectAutoNumConfigPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectAutoNumConfigPage_t qt_meta_stringdata_ProjectAutoNumConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ProjectAutoNumConfigPage"
QT_MOC_LITERAL(1, 25, 10), // "setAutoNum"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 14), // "saveCurrentTbp"
QT_MOC_LITERAL(4, 52, 12), // "loadSavedTbp"
QT_MOC_LITERAL(5, 65, 22), // "updateContextConductor"
QT_MOC_LITERAL(6, 88, 20), // "saveContextConductor"
QT_MOC_LITERAL(7, 109, 22), // "removeContextConductor"
QT_MOC_LITERAL(8, 132, 18), // "updateContextFolio"
QT_MOC_LITERAL(9, 151, 16), // "saveContextFolio"
QT_MOC_LITERAL(10, 168, 18), // "removeContextFolio"
QT_MOC_LITERAL(11, 187, 20), // "updateContextElement"
QT_MOC_LITERAL(12, 208, 18), // "saveContextElement"
QT_MOC_LITERAL(13, 227, 20), // "removeContextElement"
QT_MOC_LITERAL(14, 248, 12), // "applyAutoNum"
QT_MOC_LITERAL(15, 261, 15) // "applyManagement"

    },
    "ProjectAutoNumConfigPage\0setAutoNum\0"
    "\0saveCurrentTbp\0loadSavedTbp\0"
    "updateContextConductor\0saveContextConductor\0"
    "removeContextConductor\0updateContextFolio\0"
    "saveContextFolio\0removeContextFolio\0"
    "updateContextElement\0saveContextElement\0"
    "removeContextElement\0applyAutoNum\0"
    "applyManagement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectAutoNumConfigPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       1,    2,   92,    2, 0x06 /* Public */,
       3,    0,   97,    2, 0x06 /* Public */,
       4,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   99,    2, 0x08 /* Private */,
       6,    0,  102,    2, 0x08 /* Private */,
       7,    0,  103,    2, 0x08 /* Private */,
       8,    1,  104,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    1,  109,    2, 0x08 /* Private */,
      12,    0,  112,    2, 0x08 /* Private */,
      13,    0,  113,    2, 0x08 /* Private */,
      14,    0,  114,    2, 0x08 /* Private */,
      15,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ProjectAutoNumConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProjectAutoNumConfigPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setAutoNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setAutoNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->saveCurrentTbp(); break;
        case 3: _t->loadSavedTbp(); break;
        case 4: _t->updateContextConductor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->saveContextConductor(); break;
        case 6: _t->removeContextConductor(); break;
        case 7: _t->updateContextFolio((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->saveContextFolio(); break;
        case 9: _t->removeContextFolio(); break;
        case 10: _t->updateContextElement((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->saveContextElement(); break;
        case 12: _t->removeContextElement(); break;
        case 13: _t->applyAutoNum(); break;
        case 14: _t->applyManagement(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProjectAutoNumConfigPage::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProjectAutoNumConfigPage::setAutoNum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProjectAutoNumConfigPage::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProjectAutoNumConfigPage::setAutoNum)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProjectAutoNumConfigPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProjectAutoNumConfigPage::saveCurrentTbp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProjectAutoNumConfigPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProjectAutoNumConfigPage::loadSavedTbp)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProjectAutoNumConfigPage::staticMetaObject = { {
    QMetaObject::SuperData::link<ProjectConfigPage::staticMetaObject>(),
    qt_meta_stringdata_ProjectAutoNumConfigPage.data,
    qt_meta_data_ProjectAutoNumConfigPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProjectAutoNumConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectAutoNumConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectAutoNumConfigPage.stringdata0))
        return static_cast<void*>(this);
    return ProjectConfigPage::qt_metacast(_clname);
}

int ProjectAutoNumConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProjectConfigPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ProjectAutoNumConfigPage::setAutoNum(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProjectAutoNumConfigPage::setAutoNum(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProjectAutoNumConfigPage::saveCurrentTbp()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ProjectAutoNumConfigPage::loadSavedTbp()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
