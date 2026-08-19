/****************************************************************************
** Meta object code from reading C++ file 'terminaldata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/properties/terminaldata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'terminaldata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TerminalData_t {
    QByteArrayData data[8];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TerminalData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TerminalData_t qt_meta_stringdata_TerminalData = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TerminalData"
QT_MOC_LITERAL(1, 13, 4), // "Type"
QT_MOC_LITERAL(2, 18, 7), // "Generic"
QT_MOC_LITERAL(3, 26, 5), // "Inner"
QT_MOC_LITERAL(4, 32, 5), // "Outer"
QT_MOC_LITERAL(5, 38, 2), // "No"
QT_MOC_LITERAL(6, 41, 2), // "Nc"
QT_MOC_LITERAL(7, 44, 6) // "Common"

    },
    "TerminalData\0Type\0Generic\0Inner\0Outer\0"
    "No\0Nc\0Common"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TerminalData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    6,   19,

 // enum data: key, value
       2, uint(TerminalData::Generic),
       3, uint(TerminalData::Inner),
       4, uint(TerminalData::Outer),
       5, uint(TerminalData::No),
       6, uint(TerminalData::Nc),
       7, uint(TerminalData::Common),

       0        // eod
};

QT_INIT_METAOBJECT const QMetaObject TerminalData::staticMetaObject = { {
    QtPrivate::MetaObjectForType<PropertiesInterface>::value(),
    qt_meta_stringdata_TerminalData.data,
    qt_meta_data_TerminalData,
    nullptr,
    nullptr,
    nullptr
} };

QT_WARNING_POP
QT_END_MOC_NAMESPACE
