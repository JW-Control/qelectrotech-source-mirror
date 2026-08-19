/****************************************************************************
** Meta object code from reading C++ file 'selectautonumw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/autoNum/ui/selectautonumw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectautonumw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectAutonumW_t {
    QByteArrayData data[14];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectAutonumW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectAutonumW_t qt_meta_stringdata_SelectAutonumW = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SelectAutonumW"
QT_MOC_LITERAL(1, 15, 12), // "applyPressed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "removeClicked"
QT_MOC_LITERAL(4, 43, 21), // "on_add_button_clicked"
QT_MOC_LITERAL(5, 65, 24), // "on_remove_button_clicked"
QT_MOC_LITERAL(6, 90, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(7, 111, 16), // "QAbstractButton*"
QT_MOC_LITERAL(8, 128, 11), // "applyEnable"
QT_MOC_LITERAL(9, 140, 20), // "on_m_next_pb_clicked"
QT_MOC_LITERAL(10, 161, 24), // "on_m_previous_pb_clicked"
QT_MOC_LITERAL(11, 186, 32), // "on_m_comboBox_currentTextChanged"
QT_MOC_LITERAL(12, 219, 4), // "arg1"
QT_MOC_LITERAL(13, 224, 22) // "on_m_remove_pb_clicked"

    },
    "SelectAutonumW\0applyPressed\0\0removeClicked\0"
    "on_add_button_clicked\0on_remove_button_clicked\0"
    "on_buttonBox_clicked\0QAbstractButton*\0"
    "applyEnable\0on_m_next_pb_clicked\0"
    "on_m_previous_pb_clicked\0"
    "on_m_comboBox_currentTextChanged\0arg1\0"
    "on_m_remove_pb_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectAutonumW[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
       8,    0,   79,    2, 0x28 /* Private | MethodCloned */,
       9,    0,   80,    2, 0x08 /* Private */,
      10,    0,   81,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,

       0        // eod
};

void SelectAutonumW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectAutonumW *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->applyPressed(); break;
        case 1: _t->removeClicked(); break;
        case 2: _t->on_add_button_clicked(); break;
        case 3: _t->on_remove_button_clicked(); break;
        case 4: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 5: _t->applyEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->applyEnable(); break;
        case 7: _t->on_m_next_pb_clicked(); break;
        case 8: _t->on_m_previous_pb_clicked(); break;
        case 9: _t->on_m_comboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_m_remove_pb_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SelectAutonumW::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectAutonumW::applyPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SelectAutonumW::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectAutonumW::removeClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectAutonumW::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SelectAutonumW.data,
    qt_meta_data_SelectAutonumW,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectAutonumW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectAutonumW::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectAutonumW.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SelectAutonumW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SelectAutonumW::applyPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SelectAutonumW::removeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
