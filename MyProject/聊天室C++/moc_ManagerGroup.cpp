/****************************************************************************
** Meta object code from reading C++ file 'ManagerGroup.h'
**
** Created: Mon Mar 18 16:12:25 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ManagerGroup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManagerGroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ManagerGroup[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      60,   13,   13,   13, 0x05,
      85,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     107,   13,   13,   13, 0x0a,
     121,   13,   13,   13, 0x0a,
     135,   13,   13,   13, 0x0a,
     175,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ManagerGroup[] = {
    "ManagerGroup\0\0"
    "updateGroupNameSignal(const QVector<QString>)\0"
    "deleteGroupName(QString)\0selectedName(QString)\0"
    "deleteGroup()\0insertGroup()\0"
    "updateGroupName(const QVector<QString>)\0"
    "selectUpdateGroup()\0"
};

const QMetaObject ManagerGroup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ManagerGroup,
      qt_meta_data_ManagerGroup, 0 }
};

const QMetaObject *ManagerGroup::metaObject() const
{
    return &staticMetaObject;
}

void *ManagerGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManagerGroup))
        return static_cast<void*>(const_cast< ManagerGroup*>(this));
    return QDialog::qt_metacast(_clname);
}

int ManagerGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateGroupNameSignal((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 1: deleteGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: selectedName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: deleteGroup(); break;
        case 4: insertGroup(); break;
        case 5: updateGroupName((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 6: selectUpdateGroup(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ManagerGroup::updateGroupNameSignal(const QVector<QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ManagerGroup::deleteGroupName(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ManagerGroup::selectedName(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
