/****************************************************************************
** Meta object code from reading C++ file 'exportdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/exportdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exportdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExportDialog_t {
    QByteArrayData data[14];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExportDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExportDialog_t qt_meta_stringdata_ExportDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ExportDialog"
QT_MOC_LITERAL(1, 13, 17), // "slot_correctWidth"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 18), // "slot_correctHeight"
QT_MOC_LITERAL(4, 51, 21), // "slot_keepRatioChanged"
QT_MOC_LITERAL(5, 73, 14), // "slot_resetSize"
QT_MOC_LITERAL(6, 88, 11), // "slot_export"
QT_MOC_LITERAL(7, 100, 20), // "slot_changeUseBorder"
QT_MOC_LITERAL(8, 121, 23), // "slot_checkDiagramsCount"
QT_MOC_LITERAL(9, 145, 25), // "slot_changeFilesExtension"
QT_MOC_LITERAL(10, 171, 19), // "slot_previewDiagram"
QT_MOC_LITERAL(11, 191, 22), // "slot_exportToClipBoard"
QT_MOC_LITERAL(12, 214, 21), // "slot_selectAllClicked"
QT_MOC_LITERAL(13, 236, 23) // "slot_deSelectAllClicked"

    },
    "ExportDialog\0slot_correctWidth\0\0"
    "slot_correctHeight\0slot_keepRatioChanged\0"
    "slot_resetSize\0slot_export\0"
    "slot_changeUseBorder\0slot_checkDiagramsCount\0"
    "slot_changeFilesExtension\0slot_previewDiagram\0"
    "slot_exportToClipBoard\0slot_selectAllClicked\0"
    "slot_deSelectAllClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExportDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       3,    1,   82,    2, 0x0a /* Public */,
       4,    1,   85,    2, 0x0a /* Public */,
       5,    1,   88,    2, 0x0a /* Public */,
       6,    0,   91,    2, 0x0a /* Public */,
       7,    0,   92,    2, 0x0a /* Public */,
       8,    0,   93,    2, 0x0a /* Public */,
       9,    1,   94,    2, 0x0a /* Public */,
       9,    0,   97,    2, 0x2a /* Public | MethodCloned */,
      10,    1,   98,    2, 0x0a /* Public */,
      11,    1,  101,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExportDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExportDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_correctWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_correctHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_keepRatioChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_resetSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_export(); break;
        case 5: _t->slot_changeUseBorder(); break;
        case 6: _t->slot_checkDiagramsCount(); break;
        case 7: _t->slot_changeFilesExtension((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_changeFilesExtension(); break;
        case 9: _t->slot_previewDiagram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_exportToClipBoard((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_selectAllClicked(); break;
        case 12: _t->slot_deSelectAllClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExportDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ExportDialog.data,
    qt_meta_data_ExportDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExportDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExportDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ExportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
