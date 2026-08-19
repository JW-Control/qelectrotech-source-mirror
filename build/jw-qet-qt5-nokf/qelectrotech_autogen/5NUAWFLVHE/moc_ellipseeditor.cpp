/****************************************************************************
** Meta object code from reading C++ file 'ellipseeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/ui/ellipseeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ellipseeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EllipseEditor_t {
    QByteArrayData data[6];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EllipseEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EllipseEditor_t qt_meta_stringdata_EllipseEditor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "EllipseEditor"
QT_MOC_LITERAL(1, 14, 25), // "on_m_x_sb_editingFinished"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 25), // "on_m_y_sb_editingFinished"
QT_MOC_LITERAL(4, 67, 43), // "on_m_horizontal_diameter_sb_e..."
QT_MOC_LITERAL(5, 111, 41) // "on_m_vertical_diameter_sb_edi..."

    },
    "EllipseEditor\0on_m_x_sb_editingFinished\0"
    "\0on_m_y_sb_editingFinished\0"
    "on_m_horizontal_diameter_sb_editingFinished\0"
    "on_m_vertical_diameter_sb_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EllipseEditor[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EllipseEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EllipseEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_m_x_sb_editingFinished(); break;
        case 1: _t->on_m_y_sb_editingFinished(); break;
        case 2: _t->on_m_horizontal_diameter_sb_editingFinished(); break;
        case 3: _t->on_m_vertical_diameter_sb_editingFinished(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject EllipseEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<ElementItemEditor::staticMetaObject>(),
    qt_meta_stringdata_EllipseEditor.data,
    qt_meta_data_EllipseEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EllipseEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EllipseEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EllipseEditor.stringdata0))
        return static_cast<void*>(this);
    return ElementItemEditor::qt_metacast(_clname);
}

int EllipseEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ElementItemEditor::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
