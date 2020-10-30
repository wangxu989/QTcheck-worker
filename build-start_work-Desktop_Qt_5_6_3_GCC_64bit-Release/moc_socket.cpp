/****************************************************************************
** Meta object code from reading C++ file 'socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../start_work/socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_socket_t {
    QByteArrayData data[15];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_socket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_socket_t qt_meta_stringdata_socket = {
    {
QT_MOC_LITERAL(0, 0, 6), // "socket"
QT_MOC_LITERAL(1, 7, 11), // "insert_data"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13), // "set_tablesize"
QT_MOC_LITERAL(4, 34, 8), // "act_mode"
QT_MOC_LITERAL(5, 43, 13), // "change_status"
QT_MOC_LITERAL(6, 57, 13), // "send_rec_code"
QT_MOC_LITERAL(7, 71, 8), // "ElseInf&"
QT_MOC_LITERAL(8, 80, 7), // "confirm"
QT_MOC_LITERAL(9, 88, 12), // "change_table"
QT_MOC_LITERAL(10, 101, 10), // "delete_mes"
QT_MOC_LITERAL(11, 112, 12), // "clear_tables"
QT_MOC_LITERAL(12, 125, 14), // "confrim_finish"
QT_MOC_LITERAL(13, 140, 11), // "finish_save"
QT_MOC_LITERAL(14, 152, 8) // "read_msg"

    },
    "socket\0insert_data\0\0set_tablesize\0"
    "act_mode\0change_status\0send_rec_code\0"
    "ElseInf&\0confirm\0change_table\0delete_mes\0"
    "clear_tables\0confrim_finish\0finish_save\0"
    "read_msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_socket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    2,   77,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    0,   85,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       8,    0,   89,    2, 0x06 /* Public */,
       9,    0,   90,    2, 0x06 /* Public */,
      10,    0,   91,    2, 0x06 /* Public */,
      11,    0,   92,    2, 0x06 /* Public */,
      12,    1,   93,    2, 0x06 /* Public */,
      13,    0,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        socket *_t = static_cast<socket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->insert_data((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->set_tablesize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->act_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->change_status(); break;
        case 4: _t->send_rec_code((*reinterpret_cast< ElseInf(*)>(_a[1]))); break;
        case 5: _t->confirm(); break;
        case 6: _t->change_table(); break;
        case 7: _t->delete_mes(); break;
        case 8: _t->clear_tables(); break;
        case 9: _t->confrim_finish((*reinterpret_cast< ElseInf(*)>(_a[1]))); break;
        case 10: _t->finish_save(); break;
        case 11: _t->read_msg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (socket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::insert_data)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (socket::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::set_tablesize)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (socket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::act_mode)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::change_status)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (socket::*_t)(ElseInf & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::send_rec_code)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::confirm)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::change_table)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::delete_mes)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::clear_tables)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (socket::*_t)(ElseInf & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::confrim_finish)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::finish_save)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject socket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_socket.data,
      qt_meta_data_socket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *socket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *socket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_socket.stringdata0))
        return static_cast<void*>(const_cast< socket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void socket::insert_data(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void socket::set_tablesize(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void socket::act_mode(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void socket::change_status()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void socket::send_rec_code(ElseInf & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void socket::confirm()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void socket::change_table()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void socket::delete_mes()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void socket::clear_tables()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void socket::confrim_finish(ElseInf & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void socket::finish_save()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
