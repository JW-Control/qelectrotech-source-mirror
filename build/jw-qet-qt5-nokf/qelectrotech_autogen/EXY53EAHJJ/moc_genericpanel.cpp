/****************************************************************************
** Meta object code from reading C++ file 'genericpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/genericpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'genericpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GenericPanel_t {
    QByteArrayData data[15];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GenericPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GenericPanel_t qt_meta_stringdata_GenericPanel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GenericPanel"
QT_MOC_LITERAL(1, 13, 14), // "firstActivated"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "panelContentChanged"
QT_MOC_LITERAL(4, 49, 26), // "projectInformationsChanged"
QT_MOC_LITERAL(5, 76, 11), // "QETProject*"
QT_MOC_LITERAL(6, 88, 12), // "diagramAdded"
QT_MOC_LITERAL(7, 101, 8), // "Diagram*"
QT_MOC_LITERAL(8, 110, 14), // "diagramRemoved"
QT_MOC_LITERAL(9, 125, 27), // "projectDiagramsOrderChanged"
QT_MOC_LITERAL(10, 153, 19), // "diagramTitleChanged"
QT_MOC_LITERAL(11, 173, 26), // "templatesCollectionChanged"
QT_MOC_LITERAL(12, 200, 30), // "TitleBlockTemplatesCollection*"
QT_MOC_LITERAL(13, 231, 19), // "diagramUsedTemplate"
QT_MOC_LITERAL(14, 251, 18) // "emitFirstActivated"

    },
    "GenericPanel\0firstActivated\0\0"
    "panelContentChanged\0projectInformationsChanged\0"
    "QETProject*\0diagramAdded\0Diagram*\0"
    "diagramRemoved\0projectDiagramsOrderChanged\0"
    "diagramTitleChanged\0templatesCollectionChanged\0"
    "TitleBlockTemplatesCollection*\0"
    "diagramUsedTemplate\0emitFirstActivated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GenericPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   66,    2, 0x09 /* Protected */,
       6,    2,   69,    2, 0x09 /* Protected */,
       8,    2,   74,    2, 0x09 /* Protected */,
       9,    3,   79,    2, 0x09 /* Protected */,
      10,    1,   86,    2, 0x09 /* Protected */,
      11,    2,   89,    2, 0x09 /* Protected */,
      13,    2,   94,    2, 0x09 /* Protected */,
      14,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Bool,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    2,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    2,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    2,    2,
    QMetaType::Void,

       0        // eod
};

void GenericPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GenericPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { bool _r = _t->firstActivated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->panelContentChanged(); break;
        case 2: _t->projectInformationsChanged((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 3: _t->diagramAdded((*reinterpret_cast< QETProject*(*)>(_a[1])),(*reinterpret_cast< Diagram*(*)>(_a[2]))); break;
        case 4: _t->diagramRemoved((*reinterpret_cast< QETProject*(*)>(_a[1])),(*reinterpret_cast< Diagram*(*)>(_a[2]))); break;
        case 5: _t->projectDiagramsOrderChanged((*reinterpret_cast< QETProject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->diagramTitleChanged((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 7: _t->templatesCollectionChanged((*reinterpret_cast< TitleBlockTemplatesCollection*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->diagramUsedTemplate((*reinterpret_cast< TitleBlockTemplatesCollection*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->emitFirstActivated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = bool (GenericPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GenericPanel::firstActivated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GenericPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GenericPanel::panelContentChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GenericPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeWidget::staticMetaObject>(),
    qt_meta_stringdata_GenericPanel.data,
    qt_meta_data_GenericPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GenericPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GenericPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GenericPanel.stringdata0))
        return static_cast<void*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int GenericPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
bool GenericPanel::firstActivated()
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void GenericPanel::panelContentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
