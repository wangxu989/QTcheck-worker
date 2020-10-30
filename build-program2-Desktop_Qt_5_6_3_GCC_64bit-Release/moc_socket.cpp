/****************************************************************************
** Meta object code from reading C++ file 'socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../program2/socket.h"
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
    QByteArrayData data[13];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_socket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_socket_t qt_meta_stringdata_socket = {
    {
QT_MOC_LITERAL(0, 0, 6), // "socket"
QT_MOC_LITERAL(1, 7, 14), // "insert_plantab"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "plantab*"
QT_MOC_LITERAL(4, 32, 16), // "set_plantab_size"
QT_MOC_LITERAL(5, 49, 18), // "insert_plansteptab"
QT_MOC_LITERAL(6, 68, 12), // "plansteptab*"
QT_MOC_LITERAL(7, 81, 17), // "insert_producttab"
QT_MOC_LITERAL(8, 99, 11), // "producttab*"
QT_MOC_LITERAL(9, 111, 8), // "act_mode"
QT_MOC_LITERAL(10, 120, 16), // "send_printString"
QT_MOC_LITERAL(11, 137, 12), // "qrecode_show"
QT_MOC_LITERAL(12, 150, 8) // "read_msg"

    },
    "socket\0insert_plantab\0\0plantab*\0"
    "set_plantab_size\0insert_plansteptab\0"
    "plansteptab*\0insert_producttab\0"
    "producttab*\0act_mode\0send_printString\0"
    "qrecode_show\0read_msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_socket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    2,   57,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    1,   65,    2, 0x06 /* Public */,
       9,    1,   68,    2, 0x06 /* Public */,
      10,    0,   71,    2, 0x06 /* Public */,
      11,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
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
        case 0: _t->insert_plantab((*reinterpret_cast< plantab*(*)>(_a[1]))); break;
        case 1: _t->set_plantab_size((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->insert_plansteptab((*reinterpret_cast< plansteptab*(*)>(_a[1]))); break;
        case 3: _t->insert_producttab((*reinterpret_cast< producttab*(*)>(_a[1]))); break;
        case 4: _t->act_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->send_printString(); break;
        case 6: _t->qrecode_show(); break;
        case 7: _t->read_msg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (socket::*_t)(plantab * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::insert_plantab)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (socket::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::set_plantab_size)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (socket::*_t)(plansteptab * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::insert_plansteptab)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (socket::*_t)(producttab * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::insert_producttab)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (socket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::act_mode)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::send_printString)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (socket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socket::qrecode_show)) {
                *result = 6;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void socket::insert_plantab(plantab * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void socket::set_plantab_size(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void socket::insert_plansteptab(plansteptab * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void socket::insert_producttab(producttab * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void socket::act_mode(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void socket::send_printString()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void socket::qrecode_show()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
