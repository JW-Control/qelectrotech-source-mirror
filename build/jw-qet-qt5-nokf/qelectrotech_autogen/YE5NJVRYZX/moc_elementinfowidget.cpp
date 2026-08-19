/****************************************************************************
** Meta object code from reading C++ file 'elementinfowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/ui/elementinfowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementinfowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementInfoWidget_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementInfoWidget_t qt_meta_stringdata_ElementInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ElementInfoWidget"
QT_MOC_LITERAL(1, 18, 14), // "firstActivated"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "elementInfoChange"
QT_MOC_LITERAL(4, 52, 17), // "addCustomProperty"
QT_MOC_LITERAL(5, 70, 3), // "key"
QT_MOC_LITERAL(6, 74, 5), // "value"
QT_MOC_LITERAL(7, 80, 20), // "removeCustomProperty"
QT_MOC_LITERAL(8, 101, 28), // "CustomElementInfoPartWidget*"
QT_MOC_LITERAL(9, 130, 6) // "widget"

    },
    "ElementInfoWidget\0firstActivated\0\0"
    "elementInfoChange\0addCustomProperty\0"
    "key\0value\0removeCustomProperty\0"
    "CustomElementInfoPartWidget*\0widget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    2,   46,    2, 0x08 /* Private */,
       4,    1,   51,    2, 0x28 /* Private | MethodCloned */,
       4,    0,   54,    2, 0x28 /* Private | MethodCloned */,
       7,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ElementInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementInfoWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->firstActivated(); break;
        case 1: _t->elementInfoChange(); break;
        case 2: _t->addCustomProperty((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->addCustomProperty((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->addCustomProperty(); break;
        case 5: _t->removeCustomProperty((*reinterpret_cast< CustomElementInfoPartWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ElementInfoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractElementPropertiesEditorWidget::staticMetaObject>(),
    qt_meta_stringdata_ElementInfoWidget.data,
    qt_meta_data_ElementInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractElementPropertiesEditorWidget::qt_metacast(_clname);
}

int ElementInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractElementPropertiesEditorWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
