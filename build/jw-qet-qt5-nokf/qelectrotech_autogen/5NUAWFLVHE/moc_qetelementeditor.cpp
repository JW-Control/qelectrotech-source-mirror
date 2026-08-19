/****************************************************************************
** Meta object code from reading C++ file 'qetelementeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../sources/editor/ui/qetelementeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qetelementeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QETElementEditor_t {
    QByteArrayData data[38];
    char stringdata0[1114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QETElementEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QETElementEditor_t qt_meta_stringdata_QETElementEditor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QETElementEditor"
QT_MOC_LITERAL(1, 17, 14), // "saveToLocation"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 16), // "ElementsLocation"
QT_MOC_LITERAL(4, 50, 3), // "loc"
QT_MOC_LITERAL(5, 54, 26), // "on_m_save_action_triggered"
QT_MOC_LITERAL(6, 81, 29), // "on_m_save_as_action_triggered"
QT_MOC_LITERAL(7, 111, 29), // "on_m_select_all_act_triggered"
QT_MOC_LITERAL(8, 141, 45), // "on_m_edit_element_properties_..."
QT_MOC_LITERAL(9, 187, 25), // "on_m_new_action_triggered"
QT_MOC_LITERAL(10, 213, 26), // "on_m_open_action_triggered"
QT_MOC_LITERAL(11, 240, 36), // "on_m_open_from_file_action_tr..."
QT_MOC_LITERAL(12, 277, 34), // "on_m_save_as_file_action_trig..."
QT_MOC_LITERAL(13, 312, 32), // "on_m_export_svg_action_triggered"
QT_MOC_LITERAL(14, 345, 28), // "on_m_reload_action_triggered"
QT_MOC_LITERAL(15, 374, 26), // "on_m_quit_action_triggered"
QT_MOC_LITERAL(16, 401, 34), // "on_m_deselect_all_action_trig..."
QT_MOC_LITERAL(17, 436, 25), // "on_m_cut_action_triggered"
QT_MOC_LITERAL(18, 462, 26), // "on_m_copy_action_triggered"
QT_MOC_LITERAL(19, 489, 27), // "on_m_paste_action_triggered"
QT_MOC_LITERAL(20, 517, 35), // "on_m_paste_in_area_action_tri..."
QT_MOC_LITERAL(21, 553, 37), // "on_m_paste_from_file_action_t..."
QT_MOC_LITERAL(22, 591, 40), // "on_m_paste_from_element_actio..."
QT_MOC_LITERAL(23, 632, 38), // "on_m_revert_selection_action_..."
QT_MOC_LITERAL(24, 671, 28), // "on_m_delete_action_triggered"
QT_MOC_LITERAL(25, 700, 32), // "on_m_edit_names_action_triggered"
QT_MOC_LITERAL(26, 733, 33), // "on_m_edit_author_action_trigg..."
QT_MOC_LITERAL(27, 767, 29), // "on_m_zoom_in_action_triggered"
QT_MOC_LITERAL(28, 797, 30), // "on_m_zoom_out_action_triggered"
QT_MOC_LITERAL(29, 828, 35), // "on_m_zoom_fit_best_action_tri..."
QT_MOC_LITERAL(30, 864, 35), // "on_m_zoom_original_action_tri..."
QT_MOC_LITERAL(31, 900, 31), // "on_m_about_qet_action_triggered"
QT_MOC_LITERAL(32, 932, 28), // "on_m_online_manual_triggered"
QT_MOC_LITERAL(33, 961, 29), // "on_m_youtube_action_triggered"
QT_MOC_LITERAL(34, 991, 28), // "on_m_donate_action_triggered"
QT_MOC_LITERAL(35, 1020, 30), // "on_m_about_qt_action_triggered"
QT_MOC_LITERAL(36, 1051, 25), // "on_m_import_dxf_triggered"
QT_MOC_LITERAL(37, 1077, 36) // "on_m_import_scaled_element_tr..."

    },
    "QETElementEditor\0saveToLocation\0\0"
    "ElementsLocation\0loc\0on_m_save_action_triggered\0"
    "on_m_save_as_action_triggered\0"
    "on_m_select_all_act_triggered\0"
    "on_m_edit_element_properties_action_triggered\0"
    "on_m_new_action_triggered\0"
    "on_m_open_action_triggered\0"
    "on_m_open_from_file_action_triggered\0"
    "on_m_save_as_file_action_triggered\0"
    "on_m_export_svg_action_triggered\0"
    "on_m_reload_action_triggered\0"
    "on_m_quit_action_triggered\0"
    "on_m_deselect_all_action_triggered\0"
    "on_m_cut_action_triggered\0"
    "on_m_copy_action_triggered\0"
    "on_m_paste_action_triggered\0"
    "on_m_paste_in_area_action_triggered\0"
    "on_m_paste_from_file_action_triggered\0"
    "on_m_paste_from_element_action_triggered\0"
    "on_m_revert_selection_action_triggered\0"
    "on_m_delete_action_triggered\0"
    "on_m_edit_names_action_triggered\0"
    "on_m_edit_author_action_triggered\0"
    "on_m_zoom_in_action_triggered\0"
    "on_m_zoom_out_action_triggered\0"
    "on_m_zoom_fit_best_action_triggered\0"
    "on_m_zoom_original_action_triggered\0"
    "on_m_about_qet_action_triggered\0"
    "on_m_online_manual_triggered\0"
    "on_m_youtube_action_triggered\0"
    "on_m_donate_action_triggered\0"
    "on_m_about_qt_action_triggered\0"
    "on_m_import_dxf_triggered\0"
    "on_m_import_scaled_element_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QETElementEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  184,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  187,    2, 0x08 /* Private */,
       6,    0,  188,    2, 0x08 /* Private */,
       7,    0,  189,    2, 0x08 /* Private */,
       8,    0,  190,    2, 0x08 /* Private */,
       9,    0,  191,    2, 0x08 /* Private */,
      10,    0,  192,    2, 0x08 /* Private */,
      11,    0,  193,    2, 0x08 /* Private */,
      12,    0,  194,    2, 0x08 /* Private */,
      13,    0,  195,    2, 0x08 /* Private */,
      14,    0,  196,    2, 0x08 /* Private */,
      15,    0,  197,    2, 0x08 /* Private */,
      16,    0,  198,    2, 0x08 /* Private */,
      17,    0,  199,    2, 0x08 /* Private */,
      18,    0,  200,    2, 0x08 /* Private */,
      19,    0,  201,    2, 0x08 /* Private */,
      20,    0,  202,    2, 0x08 /* Private */,
      21,    0,  203,    2, 0x08 /* Private */,
      22,    0,  204,    2, 0x08 /* Private */,
      23,    0,  205,    2, 0x08 /* Private */,
      24,    0,  206,    2, 0x08 /* Private */,
      25,    0,  207,    2, 0x08 /* Private */,
      26,    0,  208,    2, 0x08 /* Private */,
      27,    0,  209,    2, 0x08 /* Private */,
      28,    0,  210,    2, 0x08 /* Private */,
      29,    0,  211,    2, 0x08 /* Private */,
      30,    0,  212,    2, 0x08 /* Private */,
      31,    0,  213,    2, 0x08 /* Private */,
      32,    0,  214,    2, 0x08 /* Private */,
      33,    0,  215,    2, 0x08 /* Private */,
      34,    0,  216,    2, 0x08 /* Private */,
      35,    0,  217,    2, 0x08 /* Private */,
      36,    0,  218,    2, 0x08 /* Private */,
      37,    0,  219,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QETElementEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QETElementEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveToLocation((*reinterpret_cast< ElementsLocation(*)>(_a[1]))); break;
        case 1: { bool _r = _t->on_m_save_action_triggered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->on_m_save_as_action_triggered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->on_m_select_all_act_triggered(); break;
        case 4: _t->on_m_edit_element_properties_action_triggered(); break;
        case 5: _t->on_m_new_action_triggered(); break;
        case 6: _t->on_m_open_action_triggered(); break;
        case 7: _t->on_m_open_from_file_action_triggered(); break;
        case 8: { bool _r = _t->on_m_save_as_file_action_triggered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->on_m_export_svg_action_triggered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->on_m_reload_action_triggered(); break;
        case 11: _t->on_m_quit_action_triggered(); break;
        case 12: _t->on_m_deselect_all_action_triggered(); break;
        case 13: _t->on_m_cut_action_triggered(); break;
        case 14: _t->on_m_copy_action_triggered(); break;
        case 15: _t->on_m_paste_action_triggered(); break;
        case 16: _t->on_m_paste_in_area_action_triggered(); break;
        case 17: _t->on_m_paste_from_file_action_triggered(); break;
        case 18: _t->on_m_paste_from_element_action_triggered(); break;
        case 19: _t->on_m_revert_selection_action_triggered(); break;
        case 20: _t->on_m_delete_action_triggered(); break;
        case 21: _t->on_m_edit_names_action_triggered(); break;
        case 22: _t->on_m_edit_author_action_triggered(); break;
        case 23: _t->on_m_zoom_in_action_triggered(); break;
        case 24: _t->on_m_zoom_out_action_triggered(); break;
        case 25: _t->on_m_zoom_fit_best_action_triggered(); break;
        case 26: _t->on_m_zoom_original_action_triggered(); break;
        case 27: _t->on_m_about_qet_action_triggered(); break;
        case 28: _t->on_m_online_manual_triggered(); break;
        case 29: _t->on_m_youtube_action_triggered(); break;
        case 30: _t->on_m_donate_action_triggered(); break;
        case 31: _t->on_m_about_qt_action_triggered(); break;
        case 32: _t->on_m_import_dxf_triggered(); break;
        case 33: _t->on_m_import_scaled_element_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            using _t = void (QETElementEditor::*)(ElementsLocation );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QETElementEditor::saveToLocation)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QETElementEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QETElementEditor.data,
    qt_meta_data_QETElementEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QETElementEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QETElementEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QETElementEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QETElementEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void QETElementEditor::saveToLocation(ElementsLocation _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
