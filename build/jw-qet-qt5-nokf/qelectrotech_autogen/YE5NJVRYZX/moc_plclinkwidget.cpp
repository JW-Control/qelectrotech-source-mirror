/****************************************************************************
** Meta object code from reading C++ file 'plclinkwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/plclinkwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plclinkwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlcLinkWidget_t {
    QByteArrayData data[9];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlcLinkWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlcLinkWidget_t qt_meta_stringdata_PlcLinkWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PlcLinkWidget"
QT_MOC_LITERAL(1, 14, 8), // "updateUi"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 28), // "on_m_search_field_textEdited"
QT_MOC_LITERAL(4, 53, 4), // "text"
QT_MOC_LITERAL(5, 58, 43), // "on_m_tree_widget_customContex..."
QT_MOC_LITERAL(6, 102, 3), // "pos"
QT_MOC_LITERAL(7, 106, 22), // "on_m_unlink_pb_clicked"
QT_MOC_LITERAL(8, 129, 25) // "on_m_show_this_pb_clicked"

    },
    "PlcLinkWidget\0updateUi\0\0"
    "on_m_search_field_textEdited\0text\0"
    "on_m_tree_widget_customContextMenuRequested\0"
    "pos\0on_m_unlink_pb_clicked\0"
    "on_m_show_this_pb_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlcLinkWidget[] = {

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
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QPoint,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlcLinkWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlcLinkWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateUi(); break;
        case 1: _t->on_m_search_field_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_m_tree_widget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->on_m_unlink_pb_clicked(); break;
        case 4: _t->on_m_show_this_pb_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlcLinkWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractElementPropertiesEditorWidget::staticMetaObject>(),
    qt_meta_stringdata_PlcLinkWidget.data,
    qt_meta_data_PlcLinkWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlcLinkWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlcLinkWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlcLinkWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractElementPropertiesEditorWidget::qt_metacast(_clname);
}

int PlcLinkWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractElementPropertiesEditorWidget::qt_metacall(_c, _id, _a);
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
