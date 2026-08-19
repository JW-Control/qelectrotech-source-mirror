/****************************************************************************
** Meta object code from reading C++ file 'elementpropertieseditorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/ui/elementpropertieseditorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementpropertieseditorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementPropertiesEditorWidget_t {
    QByteArrayData data[19];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementPropertiesEditorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementPropertiesEditorWidget_t qt_meta_stringdata_ElementPropertiesEditorWidget = {
    {
QT_MOC_LITERAL(0, 0, 29), // "ElementPropertiesEditorWidget"
QT_MOC_LITERAL(1, 30, 23), // "on_m_buttonBox_accepted"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 37), // "on_m_base_type_cb_currentInde..."
QT_MOC_LITERAL(4, 93, 5), // "index"
QT_MOC_LITERAL(5, 99, 34), // "on_m_slave_groups_checkbox_to..."
QT_MOC_LITERAL(6, 134, 7), // "checked"
QT_MOC_LITERAL(7, 142, 30), // "on_max_slaves_checkbox_toggled"
QT_MOC_LITERAL(8, 173, 9), // "plcAddRow"
QT_MOC_LITERAL(9, 183, 12), // "plcRemoveRow"
QT_MOC_LITERAL(10, 196, 21), // "plcPasteFromClipboard"
QT_MOC_LITERAL(11, 218, 23), // "plcTerminalCountChanged"
QT_MOC_LITERAL(12, 242, 3), // "row"
QT_MOC_LITERAL(13, 246, 5), // "count"
QT_MOC_LITERAL(14, 252, 19), // "plcSelectHeaderFont"
QT_MOC_LITERAL(15, 272, 17), // "plcSelectCellFont"
QT_MOC_LITERAL(16, 290, 19), // "plcSetCellFromValue"
QT_MOC_LITERAL(17, 310, 3), // "col"
QT_MOC_LITERAL(18, 314, 3) // "val"

    },
    "ElementPropertiesEditorWidget\0"
    "on_m_buttonBox_accepted\0\0"
    "on_m_base_type_cb_currentIndexChanged\0"
    "index\0on_m_slave_groups_checkbox_toggled\0"
    "checked\0on_max_slaves_checkbox_toggled\0"
    "plcAddRow\0plcRemoveRow\0plcPasteFromClipboard\0"
    "plcTerminalCountChanged\0row\0count\0"
    "plcSelectHeaderFont\0plcSelectCellFont\0"
    "plcSetCellFromValue\0col\0val"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementPropertiesEditorWidget[] = {

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
       3,    1,   70,    2, 0x08 /* Private */,
       5,    1,   73,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
       8,    0,   79,    2, 0x08 /* Private */,
       9,    0,   80,    2, 0x08 /* Private */,
      10,    0,   81,    2, 0x08 /* Private */,
      11,    2,   82,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    3,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   12,   17,   18,

       0        // eod
};

void ElementPropertiesEditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementPropertiesEditorWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_m_buttonBox_accepted(); break;
        case 1: _t->on_m_base_type_cb_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_m_slave_groups_checkbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_max_slaves_checkbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->plcAddRow(); break;
        case 5: _t->plcRemoveRow(); break;
        case 6: _t->plcPasteFromClipboard(); break;
        case 7: _t->plcTerminalCountChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->plcSelectHeaderFont(); break;
        case 9: _t->plcSelectCellFont(); break;
        case 10: _t->plcSetCellFromValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ElementPropertiesEditorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ElementPropertiesEditorWidget.data,
    qt_meta_data_ElementPropertiesEditorWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementPropertiesEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementPropertiesEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementPropertiesEditorWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ElementPropertiesEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
