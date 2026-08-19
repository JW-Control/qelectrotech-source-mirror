/****************************************************************************
** Meta object code from reading C++ file 'graphicstablepropertieseditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qetgraphicsitem/ViewItem/ui/graphicstablepropertieseditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicstablepropertieseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsTablePropertiesEditor_t {
    QByteArrayData data[15];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsTablePropertiesEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsTablePropertiesEditor_t qt_meta_stringdata_GraphicsTablePropertiesEditor = {
    {
QT_MOC_LITERAL(0, 0, 29), // "GraphicsTablePropertiesEditor"
QT_MOC_LITERAL(1, 30, 27), // "on_m_header_font_pb_clicked"
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 26), // "on_m_table_font_pb_clicked"
QT_MOC_LITERAL(4, 86, 8), // "updateUi"
QT_MOC_LITERAL(5, 95, 15), // "updatePosWidget"
QT_MOC_LITERAL(6, 111, 15), // "updateInfoLabel"
QT_MOC_LITERAL(7, 127, 29), // "on_m_table_name_le_textEdited"
QT_MOC_LITERAL(8, 157, 4), // "arg1"
QT_MOC_LITERAL(9, 162, 32), // "on_m_previous_table_cb_activated"
QT_MOC_LITERAL(10, 195, 5), // "index"
QT_MOC_LITERAL(11, 201, 24), // "on_m_previous_pb_clicked"
QT_MOC_LITERAL(12, 226, 20), // "on_m_next_pb_clicked"
QT_MOC_LITERAL(13, 247, 29), // "on_m_auto_geometry_pb_clicked"
QT_MOC_LITERAL(14, 277, 46) // "on_m_apply_geometry_to_linked..."

    },
    "GraphicsTablePropertiesEditor\0"
    "on_m_header_font_pb_clicked\0\0"
    "on_m_table_font_pb_clicked\0updateUi\0"
    "updatePosWidget\0updateInfoLabel\0"
    "on_m_table_name_le_textEdited\0arg1\0"
    "on_m_previous_table_cb_activated\0index\0"
    "on_m_previous_pb_clicked\0on_m_next_pb_clicked\0"
    "on_m_auto_geometry_pb_clicked\0"
    "on_m_apply_geometry_to_linked_table_pb_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsTablePropertiesEditor[] = {

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
       7,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicsTablePropertiesEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicsTablePropertiesEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_m_header_font_pb_clicked(); break;
        case 1: _t->on_m_table_font_pb_clicked(); break;
        case 2: _t->updateUi(); break;
        case 3: _t->updatePosWidget(); break;
        case 4: _t->updateInfoLabel(); break;
        case 5: _t->on_m_table_name_le_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_m_previous_table_cb_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_m_previous_pb_clicked(); break;
        case 8: _t->on_m_next_pb_clicked(); break;
        case 9: _t->on_m_auto_geometry_pb_clicked(); break;
        case 10: _t->on_m_apply_geometry_to_linked_table_pb_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicsTablePropertiesEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertiesEditorWidget::staticMetaObject>(),
    qt_meta_stringdata_GraphicsTablePropertiesEditor.data,
    qt_meta_data_GraphicsTablePropertiesEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsTablePropertiesEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsTablePropertiesEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsTablePropertiesEditor.stringdata0))
        return static_cast<void*>(this);
    return PropertiesEditorWidget::qt_metacast(_clname);
}

int GraphicsTablePropertiesEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertiesEditorWidget::qt_metacall(_c, _id, _a);
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
