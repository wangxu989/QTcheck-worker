/****************************************************************************
** Meta object code from reading C++ file 'start_finish_work.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../createtab/start_finish_work.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'start_finish_work.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_start_finish_work_t {
    QByteArrayData data[17];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_start_finish_work_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_start_finish_work_t qt_meta_stringdata_start_finish_work = {
    {
QT_MOC_LITERAL(0, 0, 17), // "start_finish_work"
QT_MOC_LITERAL(1, 18, 10), // "check_info"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "flag"
QT_MOC_LITERAL(4, 35, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(5, 59, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(6, 83, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(7, 107, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(8, 131, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(9, 155, 14), // "deal_ProcessID"
QT_MOC_LITERAL(10, 170, 8), // "QString&"
QT_MOC_LITERAL(11, 179, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(12, 201, 8), // "deal_rec"
QT_MOC_LITERAL(13, 210, 16), // "delete_start2tab"
QT_MOC_LITERAL(14, 227, 13), // "add_start2tab"
QT_MOC_LITERAL(15, 241, 9), // "start_rec"
QT_MOC_LITERAL(16, 251, 1) // "s"

    },
    "start_finish_work\0check_info\0\0flag\0"
    "on_pushButton_4_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_6_clicked\0on_pushButton_7_clicked\0"
    "on_pushButton_5_clicked\0deal_ProcessID\0"
    "QString&\0on_pushButton_clicked\0deal_rec\0"
    "delete_start2tab\0add_start2tab\0start_rec\0"
    "s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_start_finish_work[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    0,   72,    2, 0x08 /* Private */,
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,
      13,    1,   84,    2, 0x08 /* Private */,
      14,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void start_finish_work::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        start_finish_work *_t = static_cast<start_finish_work *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->check_info((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_4_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_pushButton_6_clicked(); break;
        case 4: _t->on_pushButton_7_clicked(); break;
        case 5: _t->on_pushButton_5_clicked(); break;
        case 6: _t->deal_ProcessID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->deal_rec((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->delete_start2tab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->add_start2tab((*reinterpret_cast< const start_rec(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject start_finish_work::staticMetaObject = {
    { &MyWidget::staticMetaObject, qt_meta_stringdata_start_finish_work.data,
      qt_meta_data_start_finish_work,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *start_finish_work::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *start_finish_work::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_start_finish_work.stringdata0))
        return static_cast<void*>(const_cast< start_finish_work*>(this));
    if (!strcmp(_clname, "baseP"))
        return static_cast< baseP*>(const_cast< start_finish_work*>(this));
    return MyWidget::qt_metacast(_clname);
}

int start_finish_work::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
