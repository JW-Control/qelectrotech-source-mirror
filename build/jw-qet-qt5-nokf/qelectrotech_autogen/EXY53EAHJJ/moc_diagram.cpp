/****************************************************************************
** Meta object code from reading C++ file 'diagram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/diagram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diagram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Diagram_t {
    QByteArrayData data[20];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Diagram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Diagram_t qt_meta_stringdata_Diagram = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Diagram"
QT_MOC_LITERAL(1, 8, 11), // "showDiagram"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "Diagram*"
QT_MOC_LITERAL(4, 30, 29), // "usedTitleBlockTemplateChanged"
QT_MOC_LITERAL(5, 60, 19), // "diagramTitleChanged"
QT_MOC_LITERAL(6, 80, 19), // "findElementRequired"
QT_MOC_LITERAL(7, 100, 16), // "ElementsLocation"
QT_MOC_LITERAL(8, 117, 16), // "diagramActivated"
QT_MOC_LITERAL(9, 134, 25), // "diagramInformationChanged"
QT_MOC_LITERAL(10, 160, 15), // "adjustSceneRect"
QT_MOC_LITERAL(11, 176, 12), // "titleChanged"
QT_MOC_LITERAL(12, 189, 25), // "titleBlockTemplateChanged"
QT_MOC_LITERAL(13, 215, 25), // "titleBlockTemplateRemoved"
QT_MOC_LITERAL(14, 241, 21), // "setTitleBlockTemplate"
QT_MOC_LITERAL(15, 263, 16), // "loadElmtFolioSeq"
QT_MOC_LITERAL(16, 280, 15), // "loadCndFolioSeq"
QT_MOC_LITERAL(17, 296, 9), // "selectAll"
QT_MOC_LITERAL(18, 306, 11), // "deselectAll"
QT_MOC_LITERAL(19, 318, 15) // "invertSelection"

    },
    "Diagram\0showDiagram\0\0Diagram*\0"
    "usedTitleBlockTemplateChanged\0"
    "diagramTitleChanged\0findElementRequired\0"
    "ElementsLocation\0diagramActivated\0"
    "diagramInformationChanged\0adjustSceneRect\0"
    "titleChanged\0titleBlockTemplateChanged\0"
    "titleBlockTemplateRemoved\0"
    "setTitleBlockTemplate\0loadElmtFolioSeq\0"
    "loadCndFolioSeq\0selectAll\0deselectAll\0"
    "invertSelection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagram[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       5,    1,  105,    2, 0x06 /* Public */,
       6,    1,  108,    2, 0x06 /* Public */,
       8,    0,  111,    2, 0x06 /* Public */,
       9,    0,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  113,    2, 0x0a /* Public */,
      11,    0,  114,    2, 0x0a /* Public */,
      12,    1,  115,    2, 0x0a /* Public */,
      13,    2,  118,    2, 0x0a /* Public */,
      13,    1,  123,    2, 0x2a /* Public | MethodCloned */,
      14,    1,  126,    2, 0x0a /* Public */,
      15,    0,  129,    2, 0x0a /* Public */,
      16,    0,  130,    2, 0x0a /* Public */,
      17,    0,  131,    2, 0x0a /* Public */,
      18,    0,  132,    2, 0x0a /* Public */,
      19,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Diagram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Diagram *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showDiagram((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 1: _t->usedTitleBlockTemplateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->diagramTitleChanged((*reinterpret_cast< Diagram*(*)>(_a[1]))); break;
        case 3: _t->findElementRequired((*reinterpret_cast< const ElementsLocation(*)>(_a[1]))); break;
        case 4: _t->diagramActivated(); break;
        case 5: _t->diagramInformationChanged(); break;
        case 6: _t->adjustSceneRect(); break;
        case 7: _t->titleChanged(); break;
        case 8: _t->titleBlockTemplateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->titleBlockTemplateRemoved((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->titleBlockTemplateRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->setTitleBlockTemplate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->loadElmtFolioSeq(); break;
        case 13: _t->loadCndFolioSeq(); break;
        case 14: _t->selectAll(); break;
        case 15: _t->deselectAll(); break;
        case 16: _t->invertSelection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Diagram* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Diagram* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ElementsLocation >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Diagram::*)(Diagram * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::showDiagram)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Diagram::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::usedTitleBlockTemplateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Diagram::*)(Diagram * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::diagramTitleChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Diagram::*)(const ElementsLocation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::findElementRequired)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Diagram::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::diagramActivated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Diagram::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::diagramInformationChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Diagram::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_Diagram.data,
    qt_meta_data_Diagram,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Diagram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Diagram::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Diagram.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int Diagram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void Diagram::showDiagram(Diagram * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Diagram::usedTitleBlockTemplateChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Diagram::diagramTitleChanged(Diagram * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Diagram::findElementRequired(const ElementsLocation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Diagram::diagramActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Diagram::diagramInformationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
