/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../createtab/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[25];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 13), // "change_widget"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "QWidget*"
QT_MOC_LITERAL(4, 31, 9), // "onClicked"
QT_MOC_LITERAL(5, 41, 3), // "row"
QT_MOC_LITERAL(6, 45, 6), // "column"
QT_MOC_LITERAL(7, 52, 15), // "pushButton_exit"
QT_MOC_LITERAL(8, 68, 19), // "pushButtonclickedej"
QT_MOC_LITERAL(9, 88, 17), // "pushButton_finish"
QT_MOC_LITERAL(10, 106, 9), // "ejClicked"
QT_MOC_LITERAL(11, 116, 15), // "pushform_button"
QT_MOC_LITERAL(12, 132, 11), // "start_after"
QT_MOC_LITERAL(13, 144, 10), // "tabchanged"
QT_MOC_LITERAL(14, 155, 1), // "i"
QT_MOC_LITERAL(15, 157, 5), // "login"
QT_MOC_LITERAL(16, 163, 5), // "flash"
QT_MOC_LITERAL(17, 169, 7), // "prePage"
QT_MOC_LITERAL(18, 177, 8), // "nextPage"
QT_MOC_LITERAL(19, 186, 10), // "check_info"
QT_MOC_LITERAL(20, 197, 4), // "flag"
QT_MOC_LITERAL(21, 202, 12), // "plot_enlarge"
QT_MOC_LITERAL(22, 215, 11), // "plot_narrow"
QT_MOC_LITERAL(23, 227, 11), // "in_keyboard"
QT_MOC_LITERAL(24, 239, 9) // "gauge_add"

    },
    "Dialog\0change_widget\0\0QWidget*\0onClicked\0"
    "row\0column\0pushButton_exit\0"
    "pushButtonclickedej\0pushButton_finish\0"
    "ejClicked\0pushform_button\0start_after\0"
    "tabchanged\0i\0login\0flash\0prePage\0"
    "nextPage\0check_info\0flag\0plot_enlarge\0"
    "plot_narrow\0in_keyboard\0gauge_add"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,  107,    2, 0x0a /* Public */,
       7,    0,  112,    2, 0x0a /* Public */,
       8,    0,  113,    2, 0x0a /* Public */,
       9,    0,  114,    2, 0x0a /* Public */,
      10,    2,  115,    2, 0x0a /* Public */,
      11,    0,  120,    2, 0x0a /* Public */,
      12,    0,  121,    2, 0x0a /* Public */,
      13,    1,  122,    2, 0x08 /* Private */,
      15,    0,  125,    2, 0x08 /* Private */,
      16,    0,  126,    2, 0x08 /* Private */,
      17,    0,  127,    2, 0x08 /* Private */,
      18,    0,  128,    2, 0x08 /* Private */,
      19,    1,  129,    2, 0x08 /* Private */,
      21,    0,  132,    2, 0x08 /* Private */,
      22,    0,  133,    2, 0x08 /* Private */,
      23,    2,  134,    2, 0x08 /* Private */,
      24,    0,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_widget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->onClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->pushButton_exit(); break;
        case 3: _t->pushButtonclickedej(); break;
        case 4: _t->pushButton_finish(); break;
        case 5: _t->ejClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->pushform_button(); break;
        case 7: _t->start_after(); break;
        case 8: _t->tabchanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->login(); break;
        case 10: _t->flash(); break;
        case 11: _t->prePage(); break;
        case 12: _t->nextPage(); break;
        case 13: _t->check_info((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->plot_enlarge(); break;
        case 15: _t->plot_narrow(); break;
        case 16: _t->in_keyboard((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 17: _t->gauge_add(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dialog::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::change_widget)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog.data,
      qt_meta_data_Dialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(const_cast< Dialog*>(this));
    if (!strcmp(_clname, "baseP"))
        return static_cast< baseP*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Dialog::change_widget(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
