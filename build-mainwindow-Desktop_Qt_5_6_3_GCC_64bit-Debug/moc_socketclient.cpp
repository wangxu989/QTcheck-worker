/****************************************************************************
** Meta object code from reading C++ file 'socketclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow/socketclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socketclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_socketclient_t {
    QByteArrayData data[11];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_socketclient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_socketclient_t qt_meta_stringdata_socketclient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "socketclient"
QT_MOC_LITERAL(1, 13, 11), // "insert_data"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "plot_enlarge"
QT_MOC_LITERAL(4, 39, 11), // "plot_narrow"
QT_MOC_LITERAL(5, 51, 8), // "gauge_no"
QT_MOC_LITERAL(6, 60, 13), // "QString*const"
QT_MOC_LITERAL(7, 74, 11), // "readmessage"
QT_MOC_LITERAL(8, 86, 12), // "displayError"
QT_MOC_LITERAL(9, 99, 30), // "QLocalSocket::LocalSocketError"
QT_MOC_LITERAL(10, 130, 11) // "socketError"

    },
    "socketclient\0insert_data\0\0plot_enlarge\0"
    "plot_narrow\0gauge_no\0QString*const\0"
    "readmessage\0displayError\0"
    "QLocalSocket::LocalSocketError\0"
    "socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_socketclient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    0,   47,    2, 0x06 /* Public */,
       4,    0,   48,    2, 0x06 /* Public */,
       5,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   52,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void socketclient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        socketclient *_t = static_cast<socketclient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->insert_data((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->plot_enlarge(); break;
        case 2: _t->plot_narrow(); break;
        case 3: _t->gauge_no((*reinterpret_cast< const QString*const(*)>(_a[1]))); break;
        case 4: _t->readmessage(); break;
        case 5: _t->displayError((*reinterpret_cast< QLocalSocket::LocalSocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (socketclient::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socketclient::insert_data)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (socketclient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socketclient::plot_enlarge)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (socketclient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socketclient::plot_narrow)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (socketclient::*_t)(const QString * const );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&socketclient::gauge_no)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject socketclient::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_socketclient.data,
      qt_meta_data_socketclient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *socketclient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *socketclient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_socketclient.stringdata0))
        return static_cast<void*>(const_cast< socketclient*>(this));
    return QThread::qt_metacast(_clname);
}

int socketclient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void socketclient::insert_data(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void socketclient::plot_enlarge()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void socketclient::plot_narrow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void socketclient::gauge_no(const QString * const _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
