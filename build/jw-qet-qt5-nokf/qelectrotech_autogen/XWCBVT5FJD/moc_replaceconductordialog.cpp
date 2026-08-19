/****************************************************************************
** Meta object code from reading C++ file 'replaceconductordialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/SearchAndReplace/ui/replaceconductordialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'replaceconductordialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReplaceConductorDialog_t {
    QByteArrayData data[14];
    char stringdata0[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReplaceConductorDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReplaceConductorDialog_t qt_meta_stringdata_ReplaceConductorDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ReplaceConductorDialog"
QT_MOC_LITERAL(1, 23, 29), // "on_m_erase_formula_cb_clicked"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 26), // "on_m_erase_text_cb_clicked"
QT_MOC_LITERAL(4, 81, 30), // "on_m_erase_function_cb_clicked"
QT_MOC_LITERAL(5, 112, 38), // "on_m_erase_tension_protocol_c..."
QT_MOC_LITERAL(6, 151, 34), // "on_m_erase_m_wire_color_cb_cl..."
QT_MOC_LITERAL(7, 186, 36), // "on_m_erase_m_wire_section_cb_..."
QT_MOC_LITERAL(8, 223, 21), // "on_m_earth_cb_toggled"
QT_MOC_LITERAL(9, 245, 7), // "checked"
QT_MOC_LITERAL(10, 253, 23), // "on_m_neutral_cb_toggled"
QT_MOC_LITERAL(11, 277, 30), // "on_m_update_preview_pb_clicked"
QT_MOC_LITERAL(12, 308, 21), // "on_m_color_pb_clicked"
QT_MOC_LITERAL(13, 330, 23) // "on_m_color_2_pb_clicked"

    },
    "ReplaceConductorDialog\0"
    "on_m_erase_formula_cb_clicked\0\0"
    "on_m_erase_text_cb_clicked\0"
    "on_m_erase_function_cb_clicked\0"
    "on_m_erase_tension_protocol_cb_clicked\0"
    "on_m_erase_m_wire_color_cb_clicked\0"
    "on_m_erase_m_wire_section_cb_clicked\0"
    "on_m_earth_cb_toggled\0checked\0"
    "on_m_neutral_cb_toggled\0"
    "on_m_update_preview_pb_clicked\0"
    "on_m_color_pb_clicked\0on_m_color_2_pb_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReplaceConductorDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x08 /* Private */,
      10,    1,   78,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ReplaceConductorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReplaceConductorDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_m_erase_formula_cb_clicked(); break;
        case 1: _t->on_m_erase_text_cb_clicked(); break;
        case 2: _t->on_m_erase_function_cb_clicked(); break;
        case 3: _t->on_m_erase_tension_protocol_cb_clicked(); break;
        case 4: _t->on_m_erase_m_wire_color_cb_clicked(); break;
        case 5: _t->on_m_erase_m_wire_section_cb_clicked(); break;
        case 6: _t->on_m_earth_cb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_m_neutral_cb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_m_update_preview_pb_clicked(); break;
        case 9: _t->on_m_color_pb_clicked(); break;
        case 10: _t->on_m_color_2_pb_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ReplaceConductorDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ReplaceConductorDialog.data,
    qt_meta_data_ReplaceConductorDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReplaceConductorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReplaceConductorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReplaceConductorDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ReplaceConductorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
