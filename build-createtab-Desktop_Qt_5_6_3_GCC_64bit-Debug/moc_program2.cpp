/****************************************************************************
** Meta object code from reading C++ file 'program2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../createtab/program2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'program2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Program2_t {
    QByteArrayData data[16];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Program2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Program2_t qt_meta_stringdata_Program2 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Program2"
QT_MOC_LITERAL(1, 9, 13), // "change_widget"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(4, 48, 11), // "exec_button"
QT_MOC_LITERAL(5, 60, 11), // "in_keyboard"
QT_MOC_LITERAL(6, 72, 3), // "row"
QT_MOC_LITERAL(7, 76, 6), // "column"
QT_MOC_LITERAL(8, 83, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(9, 107, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(10, 131, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(11, 155, 15), // "show_print_code"
QT_MOC_LITERAL(12, 171, 8), // "QString&"
QT_MOC_LITERAL(13, 180, 1), // "s"
QT_MOC_LITERAL(14, 182, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(15, 206, 23) // "on_pushButton_3_clicked"

    },
    "Program2\0change_widget\0\0on_pushButton_5_clicked\0"
    "exec_button\0in_keyboard\0row\0column\0"
    "on_pushButton_4_clicked\0on_pushButton_6_clicked\0"
    "on_pushButton_7_clicked\0show_print_code\0"
    "QString&\0s\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Program2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   67,    2, 0x08 /* Private */,
       4,    0,   68,    2, 0x08 /* Private */,
       5,    2,   69,    2, 0x08 /* Private */,
       8,    0,   74,    2, 0x08 /* Private */,
       9,    0,   75,    2, 0x08 /* Private */,
      10,    0,   76,    2, 0x08 /* Private */,
      11,    1,   77,    2, 0x08 /* Private */,
      14,    0,   80,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Program2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Program2 *_t = static_cast<Program2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_widget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_5_clicked(); break;
        case 2: _t->exec_button(); break;
        case 3: _t->in_keyboard((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->on_pushButton_4_clicked(); break;
        case 5: _t->on_pushButton_6_clicked(); break;
        case 6: _t->on_pushButton_7_clicked(); break;
        case 7: _t->show_print_code((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_2_clicked(); break;
        case 9: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Program2::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Program2::change_widget)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Program2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Program2.data,
      qt_meta_data_Program2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Program2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Program2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Program2.stringdata0))
        return static_cast<void*>(const_cast< Program2*>(this));
    if (!strcmp(_clname, "baseP"))
        return static_cast< baseP*>(const_cast< Program2*>(this));
    return QWidget::qt_metacast(_clname);
}

int Program2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Program2::change_widget(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
