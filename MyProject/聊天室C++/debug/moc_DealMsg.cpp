/****************************************************************************
** Meta object code from reading C++ file 'DealMsg.h'
**
** Created: Sun Dec 20 23:46:14 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DealMsg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DealMsg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DealMsg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      19,    8,    8,    8, 0x0a,
      34,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DealMsg[] = {
    "DealMsg\0\0timeOut()\0dataReceived()\0"
    "closeWin()\0"
};

const QMetaObject DealMsg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DealMsg,
      qt_meta_data_DealMsg, 0 }
};

const QMetaObject *DealMsg::metaObject() const
{
    return &staticMetaObject;
}

void *DealMsg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DealMsg))
        return static_cast<void*>(const_cast< DealMsg*>(this));
    return QObject::qt_metacast(_clname);
}

int DealMsg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timeOut(); break;
        case 1: dataReceived(); break;
        case 2: closeWin(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
