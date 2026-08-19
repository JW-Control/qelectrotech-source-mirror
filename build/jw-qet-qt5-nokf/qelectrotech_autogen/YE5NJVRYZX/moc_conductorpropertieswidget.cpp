/****************************************************************************
** Meta object code from reading C++ file 'conductorpropertieswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/conductorpropertieswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conductorpropertieswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConductorPropertiesWidget_t {
    QByteArrayData data[8];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConductorPropertiesWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConductorPropertiesWidget_t qt_meta_stringdata_ConductorPropertiesWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ConductorPropertiesWidget"
QT_MOC_LITERAL(1, 26, 13), // "updatePreview"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 1), // "b"
QT_MOC_LITERAL(4, 43, 21), // "on_m_earth_cb_toggled"
QT_MOC_LITERAL(5, 65, 7), // "checked"
QT_MOC_LITERAL(6, 73, 23), // "on_m_neutral_cb_toggled"
QT_MOC_LITERAL(7, 97, 30) // "on_m_update_preview_pb_clicked"

    },
    "ConductorPropertiesWidget\0updatePreview\0"
    "\0b\0on_m_earth_cb_toggled\0checked\0"
    "on_m_neutral_cb_toggled\0"
    "on_m_update_preview_pb_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConductorPropertiesWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       1,    0,   42,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

       0        // eod
};

void ConductorPropertiesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConductorPropertiesWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatePreview((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updatePreview(); break;
        case 2: _t->on_m_earth_cb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_m_neutral_cb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_m_update_preview_pb_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConductorPropertiesWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ConductorPropertiesWidget.data,
    qt_meta_data_ConductorPropertiesWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConductorPropertiesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConductorPropertiesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConductorPropertiesWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ConductorPropertiesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
