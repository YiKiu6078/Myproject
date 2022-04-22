/****************************************************************************
** Meta object code from reading C++ file 'socketthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IMServer/socketthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socketthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SocketThread_t {
    QByteArrayData data[16];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SocketThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SocketThread_t qt_meta_stringdata_SocketThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SocketThread"
QT_MOC_LITERAL(1, 13, 5), // "error"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(4, 44, 11), // "socketError"
QT_MOC_LITERAL(5, 56, 11), // "updateState"
QT_MOC_LITERAL(6, 68, 10), // "addNewUser"
QT_MOC_LITERAL(7, 79, 18), // "sendAddfrdToServer"
QT_MOC_LITERAL(8, 98, 15), // "sendAgreeAddFrd"
QT_MOC_LITERAL(9, 114, 21), // "sendDeleteFrdToServer"
QT_MOC_LITERAL(10, 136, 20), // "sendAddGroupToServer"
QT_MOC_LITERAL(11, 157, 19), // "sendUdpSocketThread"
QT_MOC_LITERAL(12, 177, 16), // "udpSocketThread*"
QT_MOC_LITERAL(13, 194, 17), // "sendFileHeadToRcv"
QT_MOC_LITERAL(14, 212, 19), // "rcvTcpMsgFromClient"
QT_MOC_LITERAL(15, 232, 9) // "rcvAddfrd"

    },
    "SocketThread\0error\0\0QTcpSocket::SocketError\0"
    "socketError\0updateState\0addNewUser\0"
    "sendAddfrdToServer\0sendAgreeAddFrd\0"
    "sendDeleteFrdToServer\0sendAddGroupToServer\0"
    "sendUdpSocketThread\0udpSocketThread*\0"
    "sendFileHeadToRcv\0rcvTcpMsgFromClient\0"
    "rcvAddfrd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SocketThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    2,   72,    2, 0x06 /* Public */,
       6,    5,   77,    2, 0x06 /* Public */,
       7,    2,   88,    2, 0x06 /* Public */,
       8,    2,   93,    2, 0x06 /* Public */,
       9,    2,   98,    2, 0x06 /* Public */,
      10,    2,  103,    2, 0x06 /* Public */,
      11,    1,  108,    2, 0x06 /* Public */,
      13,    4,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  120,    2, 0x08 /* Private */,
      15,    2,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

       0        // eod
};

void SocketThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SocketThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->updateState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->addNewUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 3: _t->sendAddfrdToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sendAgreeAddFrd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->sendDeleteFrdToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->sendAddGroupToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->sendUdpSocketThread((*reinterpret_cast< udpSocketThread*(*)>(_a[1]))); break;
        case 8: _t->sendFileHeadToRcv((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< qint64(*)>(_a[4]))); break;
        case 9: _t->rcvTcpMsgFromClient(); break;
        case 10: _t->rcvAddfrd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< udpSocketThread* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SocketThread::*)(QTcpSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::error)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::updateState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::addNewUser)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendAddfrdToServer)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendAgreeAddFrd)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendDeleteFrdToServer)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendAddGroupToServer)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(udpSocketThread * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendUdpSocketThread)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SocketThread::*)(QString , QString , QString , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketThread::sendFileHeadToRcv)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SocketThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_SocketThread.data,
    qt_meta_data_SocketThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SocketThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SocketThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SocketThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int SocketThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SocketThread::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SocketThread::updateState(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SocketThread::addNewUser(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SocketThread::sendAddfrdToServer(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SocketThread::sendAgreeAddFrd(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SocketThread::sendDeleteFrdToServer(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SocketThread::sendAddGroupToServer(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SocketThread::sendUdpSocketThread(udpSocketThread * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SocketThread::sendFileHeadToRcv(QString _t1, QString _t2, QString _t3, qint64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
