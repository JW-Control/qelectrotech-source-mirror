/****************************************************************************
** Meta object code from reading C++ file 'elementspanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/elementspanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementspanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElementsPanel_t {
    QByteArrayData data[25];
    char stringdata0[430];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ElementsPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ElementsPanel_t qt_meta_stringdata_ElementsPanel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ElementsPanel"
QT_MOC_LITERAL(1, 14, 17), // "requestForProject"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "QETProject*"
QT_MOC_LITERAL(4, 45, 28), // "requestForTitleBlockTemplate"
QT_MOC_LITERAL(5, 74, 26), // "TitleBlockTemplateLocation"
QT_MOC_LITERAL(6, 101, 34), // "requestForProjectPropertiesEd..."
QT_MOC_LITERAL(7, 136, 34), // "requestForDiagramPropertiesEd..."
QT_MOC_LITERAL(8, 171, 12), // "slot_clicked"
QT_MOC_LITERAL(9, 184, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(10, 201, 16), // "slot_doubleClick"
QT_MOC_LITERAL(11, 218, 6), // "reload"
QT_MOC_LITERAL(12, 225, 6), // "filter"
QT_MOC_LITERAL(13, 232, 14), // "QET::Filtering"
QT_MOC_LITERAL(14, 247, 16), // "projectWasOpened"
QT_MOC_LITERAL(15, 264, 16), // "projectWasClosed"
QT_MOC_LITERAL(16, 281, 15), // "buildFilterList"
QT_MOC_LITERAL(17, 297, 18), // "applyCurrentFilter"
QT_MOC_LITERAL(18, 316, 23), // "QList<QTreeWidgetItem*>"
QT_MOC_LITERAL(19, 340, 24), // "ensureHierarchyIsVisible"
QT_MOC_LITERAL(20, 365, 14), // "requestForItem"
QT_MOC_LITERAL(21, 380, 13), // "keyPressEvent"
QT_MOC_LITERAL(22, 394, 10), // "QKeyEvent*"
QT_MOC_LITERAL(23, 405, 5), // "event"
QT_MOC_LITERAL(24, 411, 18) // "panelContentChange"

    },
    "ElementsPanel\0requestForProject\0\0"
    "QETProject*\0requestForTitleBlockTemplate\0"
    "TitleBlockTemplateLocation\0"
    "requestForProjectPropertiesEdition\0"
    "requestForDiagramPropertiesEdition\0"
    "slot_clicked\0QTreeWidgetItem*\0"
    "slot_doubleClick\0reload\0filter\0"
    "QET::Filtering\0projectWasOpened\0"
    "projectWasClosed\0buildFilterList\0"
    "applyCurrentFilter\0QList<QTreeWidgetItem*>\0"
    "ensureHierarchyIsVisible\0requestForItem\0"
    "keyPressEvent\0QKeyEvent*\0event\0"
    "panelContentChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElementsPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,
       7,    0,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,  107,    2, 0x0a /* Public */,
      10,    2,  112,    2, 0x0a /* Public */,
      11,    0,  117,    2, 0x0a /* Public */,
      12,    2,  118,    2, 0x0a /* Public */,
      12,    1,  123,    2, 0x2a /* Public | MethodCloned */,
      14,    1,  126,    2, 0x0a /* Public */,
      15,    1,  129,    2, 0x0a /* Public */,
      16,    0,  132,    2, 0x0a /* Public */,
      17,    1,  133,    2, 0x0a /* Public */,
      19,    1,  136,    2, 0x0a /* Public */,
      20,    1,  139,    2, 0x0a /* Public */,
      21,    1,  142,    2, 0x0a /* Public */,
      24,    0,  145,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,

       0        // eod
};

void ElementsPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElementsPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->requestForProject((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 1: _t->requestForTitleBlockTemplate((*reinterpret_cast< const TitleBlockTemplateLocation(*)>(_a[1]))); break;
        case 2: _t->requestForProjectPropertiesEdition(); break;
        case 3: _t->requestForDiagramPropertiesEdition(); break;
        case 4: _t->slot_clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slot_doubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->reload(); break;
        case 7: _t->filter((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QET::Filtering(*)>(_a[2]))); break;
        case 8: _t->filter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->projectWasOpened((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 10: _t->projectWasClosed((*reinterpret_cast< QETProject*(*)>(_a[1]))); break;
        case 11: _t->buildFilterList(); break;
        case 12: _t->applyCurrentFilter((*reinterpret_cast< const QList<QTreeWidgetItem*>(*)>(_a[1]))); break;
        case 13: _t->ensureHierarchyIsVisible((*reinterpret_cast< const QList<QTreeWidgetItem*>(*)>(_a[1]))); break;
        case 14: _t->requestForItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 15: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 16: _t->panelContentChange(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TitleBlockTemplateLocation >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ElementsPanel::*)(QETProject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanel::requestForProject)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ElementsPanel::*)(const TitleBlockTemplateLocation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanel::requestForTitleBlockTemplate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ElementsPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanel::requestForProjectPropertiesEdition)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ElementsPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ElementsPanel::requestForDiagramPropertiesEdition)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ElementsPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<GenericPanel::staticMetaObject>(),
    qt_meta_stringdata_ElementsPanel.data,
    qt_meta_data_ElementsPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ElementsPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementsPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElementsPanel.stringdata0))
        return static_cast<void*>(this);
    return GenericPanel::qt_metacast(_clname);
}

int ElementsPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GenericPanel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ElementsPanel::requestForProject(QETProject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ElementsPanel::requestForTitleBlockTemplate(const TitleBlockTemplateLocation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ElementsPanel::requestForProjectPropertiesEdition()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ElementsPanel::requestForDiagramPropertiesEdition()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
