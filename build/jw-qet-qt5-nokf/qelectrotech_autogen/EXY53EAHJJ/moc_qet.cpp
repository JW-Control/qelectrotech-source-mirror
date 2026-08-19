/****************************************************************************
** Meta object code from reading C++ file 'qet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/qet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Qet_t {
    QByteArrayData data[12];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Qet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Qet_t qt_meta_stringdata_Qet = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Qet"
QT_MOC_LITERAL(1, 4, 7), // "EndType"
QT_MOC_LITERAL(2, 12, 4), // "None"
QT_MOC_LITERAL(3, 17, 6), // "Simple"
QT_MOC_LITERAL(4, 24, 8), // "Triangle"
QT_MOC_LITERAL(5, 33, 6), // "Circle"
QT_MOC_LITERAL(6, 40, 7), // "Diamond"
QT_MOC_LITERAL(7, 48, 11), // "Orientation"
QT_MOC_LITERAL(8, 60, 5), // "North"
QT_MOC_LITERAL(9, 66, 4), // "East"
QT_MOC_LITERAL(10, 71, 5), // "South"
QT_MOC_LITERAL(11, 77, 4) // "West"

    },
    "Qet\0EndType\0None\0Simple\0Triangle\0"
    "Circle\0Diamond\0Orientation\0North\0East\0"
    "South\0West"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Qet[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   24,
       7,    7, 0x0,    4,   34,

 // enum data: key, value
       2, uint(Qet::None),
       3, uint(Qet::Simple),
       4, uint(Qet::Triangle),
       5, uint(Qet::Circle),
       6, uint(Qet::Diamond),
       8, uint(Qet::North),
       9, uint(Qet::East),
      10, uint(Qet::South),
      11, uint(Qet::West),

       0        // eod
};

void Qet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Qet::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Qet.data,
    qt_meta_data_Qet,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Qet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Qet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Qet.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Qet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
