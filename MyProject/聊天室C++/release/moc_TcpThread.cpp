/****************************************************************************
** Meta object code from reading C++ file 'TcpThread.h'
**
** Created: Sun Jul 11 19:52:35 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TcpThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      19,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   10,   10,   10, 0x09,
      47,   10,   10,   10, 0x09,
      58,   10,   10,   10, 0x09,
      66,   10,   10,   10, 0x09,
      89,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TcpThread[] = {
    "TcpThread\0\0again()\0finishSend()\0"
    "progressStop()\0readFile()\0error()\0"
    "getByteWritten(qint64)\0disconnectSocket()\0"
};

const QMetaObject TcpThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TcpThread,
      qt_meta_data_TcpThread, 0 }
};

const QMetaObject *TcpThread::metaObject() const
{
    return &staticMetaObject;
}

void *TcpThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpThread))
        return static_cast<void*>(const_cast< TcpThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TcpThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: again(); break;
        case 1: finishSend(); break;
        case 2: progressStop(); break;
        case 3: readFile(); break;
        case 4: error(); break;
        case 5: getByteWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: disconnectSocket(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TcpThread::again()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TcpThread::finishSend()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
