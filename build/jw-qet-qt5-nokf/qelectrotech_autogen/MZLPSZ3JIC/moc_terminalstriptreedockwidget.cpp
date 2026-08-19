/****************************************************************************
** Meta object code from reading C++ file 'terminalstriptreedockwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/TerminalStrip/ui/terminalstriptreedockwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'terminalstriptreedockwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TerminalStripTreeDockWidget_t {
    QByteArrayData data[9];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TerminalStripTreeDockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TerminalStripTreeDockWidget_t qt_meta_stringdata_TerminalStripTreeDockWidget = {
    {
QT_MOC_LITERAL(0, 0, 27), // "TerminalStripTreeDockWidget"
QT_MOC_LITERAL(1, 28, 19), // "currentStripChanged"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 14), // "TerminalStrip*"
QT_MOC_LITERAL(4, 64, 5), // "strip"
QT_MOC_LITERAL(5, 70, 33), // "on_m_tree_view_currentItemCha..."
QT_MOC_LITERAL(6, 104, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 121, 7), // "current"
QT_MOC_LITERAL(8, 129, 8) // "previous"

    },
    "TerminalStripTreeDockWidget\0"
    "currentStripChanged\0\0TerminalStrip*\0"
    "strip\0on_m_tree_view_currentItemChanged\0"
    "QTreeWidgetItem*\0current\0previous"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TerminalStripTreeDockWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,

       0        // eod
};

void TerminalStripTreeDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TerminalStripTreeDockWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentStripChanged((*reinterpret_cast< TerminalStrip*(*)>(_a[1]))); break;
        case 1: _t->on_m_tree_view_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TerminalStripTreeDockWidget::*)(TerminalStrip * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TerminalStripTreeDockWidget::currentStripChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TerminalStripTreeDockWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_TerminalStripTreeDockWidget.data,
    qt_meta_data_TerminalStripTreeDockWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TerminalStripTreeDockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TerminalStripTreeDockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TerminalStripTreeDockWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int TerminalStripTreeDockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TerminalStripTreeDockWidget::currentStripChanged(TerminalStrip * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
