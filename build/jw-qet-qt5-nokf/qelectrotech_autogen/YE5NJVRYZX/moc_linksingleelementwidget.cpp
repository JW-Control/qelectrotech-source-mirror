/****************************************************************************
** Meta object code from reading C++ file 'linksingleelementwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/linksingleelementwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linksingleelementwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinkSingleElementWidget_t {
    QByteArrayData data[21];
    char stringdata0[391];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinkSingleElementWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinkSingleElementWidget_t qt_meta_stringdata_LinkSingleElementWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "LinkSingleElementWidget"
QT_MOC_LITERAL(1, 24, 8), // "updateUi"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "buildTree"
QT_MOC_LITERAL(4, 44, 28), // "diagramWasRemovedFromProject"
QT_MOC_LITERAL(5, 73, 23), // "showedElementWasDeleted"
QT_MOC_LITERAL(6, 97, 13), // "linkTriggered"
QT_MOC_LITERAL(7, 111, 11), // "hideButtons"
QT_MOC_LITERAL(8, 123, 11), // "showButtons"
QT_MOC_LITERAL(9, 135, 32), // "headerCustomContextMenuRequested"
QT_MOC_LITERAL(10, 168, 3), // "pos"
QT_MOC_LITERAL(11, 172, 22), // "on_m_unlink_pb_clicked"
QT_MOC_LITERAL(12, 195, 34), // "on_m_tree_widget_itemDoubleCl..."
QT_MOC_LITERAL(13, 230, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(14, 247, 4), // "item"
QT_MOC_LITERAL(15, 252, 6), // "column"
QT_MOC_LITERAL(16, 259, 43), // "on_m_tree_widget_customContex..."
QT_MOC_LITERAL(17, 303, 27), // "on_m_show_linked_pb_clicked"
QT_MOC_LITERAL(18, 331, 25), // "on_m_show_this_pb_clicked"
QT_MOC_LITERAL(19, 357, 28), // "on_m_search_field_textEdited"
QT_MOC_LITERAL(20, 386, 4) // "arg1"

    },
    "LinkSingleElementWidget\0updateUi\0\0"
    "buildTree\0diagramWasRemovedFromProject\0"
    "showedElementWasDeleted\0linkTriggered\0"
    "hideButtons\0showButtons\0"
    "headerCustomContextMenuRequested\0pos\0"
    "on_m_unlink_pb_clicked\0"
    "on_m_tree_widget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_m_tree_widget_customContextMenuRequested\0"
    "on_m_show_linked_pb_clicked\0"
    "on_m_show_this_pb_clicked\0"
    "on_m_search_field_textEdited\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinkSingleElementWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    1,   91,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    2,   95,    2, 0x08 /* Private */,
      16,    1,  100,    2, 0x08 /* Private */,
      17,    0,  103,    2, 0x08 /* Private */,
      18,    0,  104,    2, 0x08 /* Private */,
      19,    1,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QPoint,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void LinkSingleElementWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinkSingleElementWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateUi(); break;
        case 1: _t->buildTree(); break;
        case 2: _t->diagramWasRemovedFromProject(); break;
        case 3: _t->showedElementWasDeleted(); break;
        case 4: _t->linkTriggered(); break;
        case 5: _t->hideButtons(); break;
        case 6: _t->showButtons(); break;
        case 7: _t->headerCustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: _t->on_m_unlink_pb_clicked(); break;
        case 9: _t->on_m_tree_widget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_m_tree_widget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->on_m_show_linked_pb_clicked(); break;
        case 12: _t->on_m_show_this_pb_clicked(); break;
        case 13: _t->on_m_search_field_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LinkSingleElementWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractElementPropertiesEditorWidget::staticMetaObject>(),
    qt_meta_stringdata_LinkSingleElementWidget.data,
    qt_meta_data_LinkSingleElementWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LinkSingleElementWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinkSingleElementWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinkSingleElementWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractElementPropertiesEditorWidget::qt_metacast(_clname);
}

int LinkSingleElementWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractElementPropertiesEditorWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
