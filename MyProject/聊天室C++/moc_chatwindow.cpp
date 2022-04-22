/****************************************************************************
** Meta object code from reading C++ file 'chatwindow.h'
**
** Created: Mon Mar 18 16:12:39 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chatwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChatWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   11,   11,   11, 0x0a,
      49,   11,   11,   11, 0x0a,
      63,   11,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      94,   11,   11,   11, 0x0a,
     109,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     142,   11,   11,   11, 0x0a,
     160,   11,   11,   11, 0x0a,
     171,   11,   11,   11, 0x0a,
     184,   11,   11,   11, 0x0a,
     196,   11,   11,   11, 0x0a,
     212,  208,   11,   11, 0x0a,
     258,   11,   11,   11, 0x0a,
     272,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChatWindow[] = {
    "ChatWindow\0\0currentFontSize(QString)\0"
    "clearChat()\0closeLogWnd()\0clearChatLog()\0"
    "slotExtension()\0slotWriteLog()\0"
    "slotSendFile()\0slotFont(QString)\0"
    "slotSize(QString)\0slotBold()\0slotItalic()\0"
    "slotUnder()\0slotColor()\0fmt\0"
    "slotCurrentCharFormatChanged(QTextCharFormat)\0"
    "slotsendmsg()\0sendFileMsg()\0"
};

const QMetaObject ChatWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChatWindow,
      qt_meta_data_ChatWindow, 0 }
};

const QMetaObject *ChatWindow::metaObject() const
{
    return &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWindow))
        return static_cast<void*>(const_cast< ChatWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentFontSize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: clearChat(); break;
        case 2: closeLogWnd(); break;
        case 3: clearChatLog(); break;
        case 4: slotExtension(); break;
        case 5: slotWriteLog(); break;
        case 6: slotSendFile(); break;
        case 7: slotFont((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: slotSize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: slotBold(); break;
        case 10: slotItalic(); break;
        case 11: slotUnder(); break;
        case 12: slotColor(); break;
        case 13: slotCurrentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 14: slotsendmsg(); break;
        case 15: sendFileMsg(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ChatWindow::currentFontSize(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
