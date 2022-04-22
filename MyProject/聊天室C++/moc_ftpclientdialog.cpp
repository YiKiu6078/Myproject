/****************************************************************************
** Meta object code from reading C++ file 'ftpclientdialog.h'
**
** Created: Mon Mar 18 16:12:37 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ftpclientdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpclientdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ftpClientDialog[] = {

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
      37,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   16,   16,   16, 0x0a,
      72,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ftpClientDialog[] = {
    "ftpClientDialog\0\0acceptFile(QString)\0"
    "refuseFile(QString)\0slotsgetFile()\0"
    "slotRefuseFile()\0"
};

const QMetaObject ftpClientDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ftpClientDialog,
      qt_meta_data_ftpClientDialog, 0 }
};

const QMetaObject *ftpClientDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ftpClientDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ftpClientDialog))
        return static_cast<void*>(const_cast< ftpClientDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ftpClientDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: refuseFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: slotsgetFile(); break;
        case 3: slotRefuseFile(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ftpClientDialog::acceptFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ftpClientDialog::refuseFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
