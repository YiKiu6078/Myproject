/****************************************************************************
** Meta object code from reading C++ file 'UpdateGroupWnd.h'
**
** Created: Mon Mar 18 16:12:19 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "UpdateGroupWnd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateGroupWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpdateGroupWnd[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   15,   15,   15, 0x0a,
      76,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UpdateGroupWnd[] = {
    "UpdateGroupWnd\0\0"
    "updateGroupNameSignal(const QVector<QString>)\0"
    "updateGroup()\0updateSelectedName(QString)\0"
};

const QMetaObject UpdateGroupWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UpdateGroupWnd,
      qt_meta_data_UpdateGroupWnd, 0 }
};

const QMetaObject *UpdateGroupWnd::metaObject() const
{
    return &staticMetaObject;
}

void *UpdateGroupWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateGroupWnd))
        return static_cast<void*>(const_cast< UpdateGroupWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int UpdateGroupWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateGroupNameSignal((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 1: updateGroup(); break;
        case 2: updateSelectedName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UpdateGroupWnd::updateGroupNameSignal(const QVector<QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
