/****************************************************************************
** Meta object code from reading C++ file 'ftpserverdialog.h'
**
** Created: Mon Mar 18 16:12:36 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ftpserverdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpserverdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FtpServerDialog[] = {

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
      31,   16,   16,   16, 0x0a,
      48,   16,   16,   16, 0x0a,
      64,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FtpServerDialog[] = {
    "FtpServerDialog\0\0sendFileMsg()\0"
    "slotsStartSend()\0slotsOpenFile()\0"
    "clearFileName()\0"
};

const QMetaObject FtpServerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FtpServerDialog,
      qt_meta_data_FtpServerDialog, 0 }
};

const QMetaObject *FtpServerDialog::metaObject() const
{
    return &staticMetaObject;
}

void *FtpServerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FtpServerDialog))
        return static_cast<void*>(const_cast< FtpServerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FtpServerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendFileMsg(); break;
        case 1: slotsStartSend(); break;
        case 2: slotsOpenFile(); break;
        case 3: clearFileName(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FtpServerDialog::sendFileMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
