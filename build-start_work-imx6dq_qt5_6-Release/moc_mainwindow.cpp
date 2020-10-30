/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../start_work/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "insert_data"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "flag"
QT_MOC_LITERAL(4, 29, 8), // "my_send1"
QT_MOC_LITERAL(5, 38, 8), // "my_send2"
QT_MOC_LITERAL(6, 47, 8), // "my_send3"
QT_MOC_LITERAL(7, 56, 8), // "my_send4"
QT_MOC_LITERAL(8, 65, 14), // "set_table_size"
QT_MOC_LITERAL(9, 80, 3), // "num"
QT_MOC_LITERAL(10, 84, 4), // "size"
QT_MOC_LITERAL(11, 89, 8), // "act_mode"
QT_MOC_LITERAL(12, 98, 3), // "act"
QT_MOC_LITERAL(13, 102, 7), // "my_read"
QT_MOC_LITERAL(14, 110, 13), // "change_status"
QT_MOC_LITERAL(15, 124, 13), // "insert_table2"
QT_MOC_LITERAL(16, 138, 8), // "ElseInf&"
QT_MOC_LITERAL(17, 147, 7), // "confirm"
QT_MOC_LITERAL(18, 155, 12), // "change_table"
QT_MOC_LITERAL(19, 168, 10), // "delete_msg"
QT_MOC_LITERAL(20, 179, 14) // "confirm_finish"

    },
    "MainWindow\0insert_data\0\0flag\0my_send1\0"
    "my_send2\0my_send3\0my_send4\0set_table_size\0"
    "num\0size\0act_mode\0act\0my_read\0"
    "change_status\0insert_table2\0ElseInf&\0"
    "confirm\0change_table\0delete_msg\0"
    "confirm_finish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    2,   91,    2, 0x08 /* Private */,
      11,    1,   96,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    1,  101,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x08 /* Private */,
      18,    0,  105,    2, 0x08 /* Private */,
      19,    0,  106,    2, 0x08 /* Private */,
      20,    1,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->insert_data((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->my_send1(); break;
        case 2: _t->my_send2(); break;
        case 3: _t->my_send3(); break;
        case 4: _t->my_send4(); break;
        case 5: _t->set_table_size((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->act_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->my_read(); break;
        case 8: _t->change_status(); break;
        case 9: _t->insert_table2((*reinterpret_cast< ElseInf(*)>(_a[1]))); break;
        case 10: _t->confirm(); break;
        case 11: _t->change_table(); break;
        case 12: _t->delete_msg(); break;
        case 13: _t->confirm_finish((*reinterpret_cast< ElseInf(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
