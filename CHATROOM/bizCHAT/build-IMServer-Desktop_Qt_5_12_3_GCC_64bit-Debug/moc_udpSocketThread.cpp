/****************************************************************************
** Meta object code from reading C++ file 'udpSocketThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IMServer/udpSocketThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpSocketThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_udpSocketThread_t {
    QByteArrayData data[5];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_udpSocketThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_udpSocketThread_t qt_meta_stringdata_udpSocketThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "udpSocketThread"
QT_MOC_LITERAL(1, 16, 13), // "ChatMsgSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "memberOfGroupImg"
QT_MOC_LITERAL(4, 48, 19) // "rcvUdpMsgFromClient"

    },
    "udpSocketThread\0ChatMsgSignal\0\0"
    "memberOfGroupImg\0rcvUdpMsgFromClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_udpSocketThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       3,    2,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void udpSocketThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<udpSocketThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChatMsgSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->memberOfGroupImg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->rcvUdpMsgFromClient(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (udpSocketThread::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpSocketThread::ChatMsgSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (udpSocketThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpSocketThread::memberOfGroupImg)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject udpSocketThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_udpSocketThread.data,
    qt_meta_data_udpSocketThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *udpSocketThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *udpSocketThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_udpSocketThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int udpSocketThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void udpSocketThread::ChatMsgSignal(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void udpSocketThread::memberOfGroupImg(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
