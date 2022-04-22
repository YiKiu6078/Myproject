/****************************************************************************
** Meta object code from reading C++ file 'userui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IMServer/userui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserUI_t {
    QByteArrayData data[19];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserUI_t qt_meta_stringdata_UserUI = {
    {
QT_MOC_LITERAL(0, 0, 6), // "UserUI"
QT_MOC_LITERAL(1, 7, 21), // "showUserSummaryWidget"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "showCreateUserWidget"
QT_MOC_LITERAL(4, 51, 20), // "showSearchUserWidget"
QT_MOC_LITERAL(5, 72, 24), // "showConfirmCreateUserBtn"
QT_MOC_LITERAL(6, 97, 23), // "showCancelCreateUserBtn"
QT_MOC_LITERAL(7, 121, 18), // "showUserPersonInfo"
QT_MOC_LITERAL(8, 140, 3), // "row"
QT_MOC_LITERAL(9, 144, 6), // "column"
QT_MOC_LITERAL(10, 151, 20), // "showUserPersonFriend"
QT_MOC_LITERAL(11, 172, 19), // "showUserPersonGroup"
QT_MOC_LITERAL(12, 192, 22), // "showUserPersonPassword"
QT_MOC_LITERAL(13, 215, 21), // "showUserPersonDeleted"
QT_MOC_LITERAL(14, 237, 18), // "showModifyPassword"
QT_MOC_LITERAL(15, 256, 14), // "showDeleteUser"
QT_MOC_LITERAL(16, 271, 13), // "showDeleteFrd"
QT_MOC_LITERAL(17, 285, 14), // "rcvUpdateState"
QT_MOC_LITERAL(18, 300, 13) // "rcvAddNewUser"

    },
    "UserUI\0showUserSummaryWidget\0\0"
    "showCreateUserWidget\0showSearchUserWidget\0"
    "showConfirmCreateUserBtn\0"
    "showCancelCreateUserBtn\0showUserPersonInfo\0"
    "row\0column\0showUserPersonFriend\0"
    "showUserPersonGroup\0showUserPersonPassword\0"
    "showUserPersonDeleted\0showModifyPassword\0"
    "showDeleteUser\0showDeleteFrd\0"
    "rcvUpdateState\0rcvAddNewUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    2,   99,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
      10,    0,  105,    2, 0x0a /* Public */,
      11,    0,  106,    2, 0x0a /* Public */,
      12,    0,  107,    2, 0x0a /* Public */,
      13,    0,  108,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    0,  111,    2, 0x0a /* Public */,
      17,    2,  112,    2, 0x08 /* Private */,
      18,    5,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,

       0        // eod
};

void UserUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showUserSummaryWidget(); break;
        case 1: _t->showCreateUserWidget(); break;
        case 2: _t->showSearchUserWidget(); break;
        case 3: _t->showConfirmCreateUserBtn(); break;
        case 4: _t->showCancelCreateUserBtn(); break;
        case 5: _t->showUserPersonInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->showUserPersonInfo(); break;
        case 7: _t->showUserPersonFriend(); break;
        case 8: _t->showUserPersonGroup(); break;
        case 9: _t->showUserPersonPassword(); break;
        case 10: _t->showUserPersonDeleted(); break;
        case 11: _t->showModifyPassword(); break;
        case 12: _t->showDeleteUser(); break;
        case 13: _t->showDeleteFrd(); break;
        case 14: _t->rcvUpdateState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->rcvAddNewUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_UserUI.data,
    qt_meta_data_UserUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
