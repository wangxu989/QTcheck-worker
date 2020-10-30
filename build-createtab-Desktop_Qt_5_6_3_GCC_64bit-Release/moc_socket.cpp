/****************************************************************************
** Meta object code from reading C++ file 'socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../createtab/socket.h"
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
    QByteArrayData data[20];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_socket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_socket_t qt_meta_stringdata_socket = {
    {
QT_MOC_LITERAL(0, 0, 6), // "socket"
QT_MOC_LITERAL(1, 7, 10), // "start_work"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 14), // "check_identity"
QT_MOC_LITERAL(4, 34, 10), // "check_info"
QT_MOC_LITERAL(5, 45, 12), // "print_String"
QT_MOC_LITERAL(6, 58, 8), // "QString&"
QT_MOC_LITERAL(7, 67, 16), // "transf_processID"
QT_MOC_LITERAL(8, 84, 1), // "s"
QT_MOC_LITERAL(9, 86, 8), // "deal_rec"
QT_MOC_LITERAL(10, 95, 16), // "delete_start2tab"
QT_MOC_LITERAL(11, 112, 13), // "add_start2tab"
QT_MOC_LITERAL(12, 126, 10), // "start_rec&"
QT_MOC_LITERAL(13, 137, 21), // "finish_work_processID"
QT_MOC_LITERAL(14, 159, 13), // "my_connection"
QT_MOC_LITERAL(15, 173, 14), // "delete_connect"
QT_MOC_LITERAL(16, 188, 8), // "sendpoit"
QT_MOC_LITERAL(17, 197, 12), // "displayError"
QT_MOC_LITERAL(18, 210, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(19, 239, 12) // "read_message"

    },
    "socket\0start_work\0\0check_identity\0"
    "check_info\0print_String\0QString&\0"
    "transf_processID\0s\0deal_rec\0"
    "delete_start2tab\0add_start2tab\0"
    "start_rec&\0finish_work_processID\0"
    "my_connection\0delete_connect\0sendpoit\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "read_message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_socket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,
       5,    1,   89,    2, 0x06 /* Public */,
       7,    1,   92,    2, 0x06 /* Public */,
       9,    1,   95,    2, 0x06 /* Public */,
      10,    1,   98,    2, 0x06 /* Public */,
      11,    1,  101,    2, 0x06 /* Public */,
      13,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  107,    2, 0x0a /* Public */,
      15,    0,  108,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x0a /* Public */,
      17,    1,  110,    2, 0x0a /* Public */,
      19,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    8,
    QMetaType::Void, 0x80000000 | 6,    8,
    QMetaType::Void, 0x80000000 | 6,    8,
    QMetaType::Void, 0x80000000 | 12,    8,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void,

       0        // eod
};

void socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        socket *_t = static_cast<socket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_work(); break;
        case 1: _t->check_identity(); break;
        case 2: _t->check_info((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->print_String((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->transf_processID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->deal_rec((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->delete_start2tab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->add_start2tab((*reinterpret_cast< start_rec(*)>(_a[1]))); break;
        case 8: _t->finish_work_processID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->my_connection(); break;
        case 10: _t->delete_connect(); break;
        case 11: _t->sendpoit(); break;
        case 12: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->read_message(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::start_work)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::check_identity)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (socket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::check_info)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (socket::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::print_String)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (socket::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::transf_processID)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (socket::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::deal_rec)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (socket::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::delete_start2tab)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (socket::*_t)(start_rec & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::add_start2tab)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (socket::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::finish_work_processID)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject socket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_socket.data,
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
    return QObject::qt_metacast(_clname);
}

int socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void socket::start_work()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void socket::check_identity()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void socket::check_info(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void socket::print_String(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void socket::transf_processID(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void socket::deal_rec(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void socket::delete_start2tab(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void socket::add_start2tab(start_rec & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void socket::finish_work_processID(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
