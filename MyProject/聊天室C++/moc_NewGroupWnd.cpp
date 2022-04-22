/****************************************************************************
** Meta object code from reading C++ file 'NewGroupWnd.h'
**
** Created: Mon Mar 18 16:12:28 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NewGroupWnd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewGroupWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewGroupWnd[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   12,   12,   12, 0x0a,
      46,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewGroupWnd[] = {
    "NewGroupWnd\0\0insertGroupName(QString)\0"
    "clear()\0newGroup()\0"
};

const QMetaObject NewGroupWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewGroupWnd,
      qt_meta_data_NewGroupWnd, 0 }
};

const QMetaObject *NewGroupWnd::metaObject() const
{
    return &staticMetaObject;
}

void *NewGroupWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewGroupWnd))
        return static_cast<void*>(const_cast< NewGroupWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewGroupWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: insertGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: clear(); break;
        case 2: newGroup(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void NewGroupWnd::insertGroupName(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
