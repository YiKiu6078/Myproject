/****************************************************************************
** Meta object code from reading C++ file 'TcpServerThread.h'
**
** Created: Sun Jul 11 19:52:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpServerThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpServerThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TcpServerThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   16,   16,   16, 0x0a,
      57,   51,   16,   16, 0x0a,
      74,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TcpServerThread[] = {
    "TcpServerThread\0\0disconnectServer()\0"
    "progressStop()\0bytes\0showProcess(int)\0"
    "disConnectServer()\0"
};

const QMetaObject TcpServerThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TcpServerThread,
      qt_meta_data_TcpServerThread, 0 }
};

const QMetaObject *TcpServerThread::metaObject() const
{
    return &staticMetaObject;
}

void *TcpServerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpServerThread))
        return static_cast<void*>(const_cast< TcpServerThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TcpServerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: disconnectServer(); break;
        case 1: progressStop(); break;
        case 2: showProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: disConnectServer(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TcpServerThread::disconnectServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
