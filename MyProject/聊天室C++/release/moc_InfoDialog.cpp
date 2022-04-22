/****************************************************************************
** Meta object code from reading C++ file 'InfoDialog.h'
**
** Created: Sun Jul 11 19:52:46 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../InfoDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InfoDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InfoDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InfoDialog[] = {
    "InfoDialog\0\0update()\0makeSure()\0"
    "updateHead()\0"
};

const QMetaObject InfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InfoDialog,
      qt_meta_data_InfoDialog, 0 }
};

const QMetaObject *InfoDialog::metaObject() const
{
    return &staticMetaObject;
}

void *InfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfoDialog))
        return static_cast<void*>(const_cast< InfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update(); break;
        case 1: makeSure(); break;
        case 2: updateHead(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void InfoDialog::update()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
