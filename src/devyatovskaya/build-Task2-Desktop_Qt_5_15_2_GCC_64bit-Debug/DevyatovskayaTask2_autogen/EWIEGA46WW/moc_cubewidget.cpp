/****************************************************************************
** Meta object code from reading C++ file 'cubewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../../Task2/cubewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CubeWidget_t {
    QByteArrayData data[12];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CubeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CubeWidget_t qt_meta_stringdata_CubeWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CubeWidget"
QT_MOC_LITERAL(1, 11, 17), // "show_color_dialog"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "show_morph_dialog"
QT_MOC_LITERAL(4, 48, 16), // "set_morph_factor"
QT_MOC_LITERAL(5, 65, 12), // "morph_factor"
QT_MOC_LITERAL(6, 78, 11), // "update_grid"
QT_MOC_LITERAL(7, 90, 6), // "size_t"
QT_MOC_LITERAL(8, 97, 9), // "grid_step"
QT_MOC_LITERAL(9, 107, 14), // "set_cube_color"
QT_MOC_LITERAL(10, 122, 5), // "color"
QT_MOC_LITERAL(11, 128, 16) // "set_random_color"

    },
    "CubeWidget\0show_color_dialog\0\0"
    "show_morph_dialog\0set_morph_factor\0"
    "morph_factor\0update_grid\0size_t\0"
    "grid_step\0set_cube_color\0color\0"
    "set_random_color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CubeWidget[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       9,    1,   52,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QColor,   10,
    QMetaType::Void,

       0        // eod
};

void CubeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CubeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show_color_dialog(); break;
        case 1: _t->show_morph_dialog(); break;
        case 2: _t->set_morph_factor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->update_grid((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 4: _t->set_cube_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->set_random_color(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CubeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_CubeWidget.data,
    qt_meta_data_CubeWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CubeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CubeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CubeWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int CubeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
