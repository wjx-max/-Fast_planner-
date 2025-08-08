/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/nrypp_hmi/include/nrypp_hmi/main_window.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_nrypp_hmi__MainWindow_t {
    QByteArrayData data[11];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nrypp_hmi__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nrypp_hmi__MainWindow_t qt_meta_stringdata_nrypp_hmi__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "nrypp_hmi::MainWindow"
QT_MOC_LITERAL(1, 22, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 26), // "on_pushButton_init_clicked"
QT_MOC_LITERAL(4, 75, 29), // "on_pushButton_control_clicked"
QT_MOC_LITERAL(5, 105, 28), // "on_pushButton_random_clicked"
QT_MOC_LITERAL(6, 134, 28), // "on_pushButton_massed_clicked"
QT_MOC_LITERAL(7, 163, 26), // "on_pushButton_open_clicked"
QT_MOC_LITERAL(8, 190, 27), // "on_pushButton_close_clicked"
QT_MOC_LITERAL(9, 218, 26), // "on_pushButton_move_clicked"
QT_MOC_LITERAL(10, 245, 28) // "on_pushButton_change_clicked"

    },
    "nrypp_hmi::MainWindow\0on_actionAbout_triggered\0"
    "\0on_pushButton_init_clicked\0"
    "on_pushButton_control_clicked\0"
    "on_pushButton_random_clicked\0"
    "on_pushButton_massed_clicked\0"
    "on_pushButton_open_clicked\0"
    "on_pushButton_close_clicked\0"
    "on_pushButton_move_clicked\0"
    "on_pushButton_change_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nrypp_hmi__MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
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

void nrypp_hmi::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionAbout_triggered(); break;
        case 1: _t->on_pushButton_init_clicked(); break;
        case 2: _t->on_pushButton_control_clicked(); break;
        case 3: _t->on_pushButton_random_clicked(); break;
        case 4: _t->on_pushButton_massed_clicked(); break;
        case 5: _t->on_pushButton_open_clicked(); break;
        case 6: _t->on_pushButton_close_clicked(); break;
        case 7: _t->on_pushButton_move_clicked(); break;
        case 8: _t->on_pushButton_change_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject nrypp_hmi::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_nrypp_hmi__MainWindow.data,
      qt_meta_data_nrypp_hmi__MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *nrypp_hmi::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nrypp_hmi::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_nrypp_hmi__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int nrypp_hmi::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
