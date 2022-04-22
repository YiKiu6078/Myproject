/****************************************************************************
** Meta object code from reading C++ file 'MasterControl.h'
**
** Created: Wed Jul 14 16:00:48 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MasterControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MasterControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MasterControl[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      35,   30,   14,   14, 0x0a,
      52,   14,   14,   14, 0x0a,
      72,   63,   14,   14, 0x0a,
      92,   63,   14,   14, 0x0a,
     112,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MasterControl[] = {
    "MasterControl\0\0dataReceived()\0user\0"
    "reOutLogin(User)\0outLogin()\0fileName\0"
    "acceptFile(QString)\0refuseFile(QString)\0"
    "revThread()\0"
};

const QMetaObject MasterControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MasterControl,
      qt_meta_data_MasterControl, 0 }
};

const QMetaObject *MasterControl::metaObject() const
{
    return &staticMetaObject;
}

void *MasterControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MasterControl))
        return static_cast<void*>(const_cast< MasterControl*>(this));
    return QObject::qt_metacast(_clname);
}

int MasterControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataReceived(); break;
        case 1: reOutLogin((*reinterpret_cast< const User(*)>(_a[1]))); break;
        case 2: outLogin(); break;
        case 3: acceptFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: refuseFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: revThread(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
