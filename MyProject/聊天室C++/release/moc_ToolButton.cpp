/****************************************************************************
** Meta object code from reading C++ file 'ToolButton.h'
**
** Created: Sun Jul 11 19:52:48 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ToolButton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      25,   11,   11,   11, 0x05,
      50,   48,   11,   11, 0x05,
      84,   11,   11,   11, 0x05,
     109,   11,   11,   11, 0x05,
     140,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     186,   11,   11,   11, 0x0a,
     196,   11,   11,   11, 0x0a,
     207,   11,   11,   11, 0x0a,
     232,   11,   11,   11, 0x0a,
     249,   11,   11,   11, 0x0a,
     264,   11,   11,   11, 0x0a,
     279,   11,   11,   11, 0x0a,
     297,   11,   11,   11, 0x0a,
     311,   11,   11,   11, 0x0a,
     333,   11,   11,   11, 0x0a,
     362,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ToolButton[] = {
    "ToolButton\0\0update(User)\0"
    "setAction(ToolButton*)\0,\0"
    "moveToOtherGroup(ToolButton*,int)\0"
    "insertGroupName(QString)\0"
    "deleteGroupNameSignal(QString)\0"
    "updateGroupNameSignal(const QVector<QString>)\0"
    "sendMsg()\0sendFile()\0updateGroupName(QString)\0"
    "updateUserInfo()\0lookUserInfo()\0"
    "addGroupInfo()\0manageGroupInfo()\0"
    "setUserSlot()\0moveToGroup(QAction*)\0"
    "deleteGroupNameSlot(QString)\0"
    "updateGroupNameSlot(const QVector<QString>)\0"
};

const QMetaObject ToolButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_ToolButton,
      qt_meta_data_ToolButton, 0 }
};

const QMetaObject *ToolButton::metaObject() const
{
    return &staticMetaObject;
}

void *ToolButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolButton))
        return static_cast<void*>(const_cast< ToolButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int ToolButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update((*reinterpret_cast< User(*)>(_a[1]))); break;
        case 1: setAction((*reinterpret_cast< ToolButton*(*)>(_a[1]))); break;
        case 2: moveToOtherGroup((*reinterpret_cast< ToolButton*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: insertGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: deleteGroupNameSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: updateGroupNameSignal((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 6: sendMsg(); break;
        case 7: sendFile(); break;
        case 8: updateGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: updateUserInfo(); break;
        case 10: lookUserInfo(); break;
        case 11: addGroupInfo(); break;
        case 12: manageGroupInfo(); break;
        case 13: setUserSlot(); break;
        case 14: moveToGroup((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 15: deleteGroupNameSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: updateGroupNameSlot((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ToolButton::update(User _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ToolButton::setAction(ToolButton * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ToolButton::moveToOtherGroup(ToolButton * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ToolButton::insertGroupName(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ToolButton::deleteGroupNameSignal(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ToolButton::updateGroupNameSignal(const QVector<QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
