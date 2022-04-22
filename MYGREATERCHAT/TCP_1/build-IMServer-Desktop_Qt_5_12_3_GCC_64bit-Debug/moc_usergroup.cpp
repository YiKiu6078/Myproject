/****************************************************************************
** Meta object code from reading C++ file 'usergroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IMServer/usergroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usergroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserGroup_t {
    QByteArrayData data[7];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserGroup_t qt_meta_stringdata_UserGroup = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UserGroup"
QT_MOC_LITERAL(1, 10, 22), // "showGroupSummaryWidget"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "showPersonOfGroup"
QT_MOC_LITERAL(4, 52, 22), // "showCreateGeoupsWidget"
QT_MOC_LITERAL(5, 75, 17), // "showGroupListInfo"
QT_MOC_LITERAL(6, 93, 17) // "showDeleteOfGroup"

    },
    "UserGroup\0showGroupSummaryWidget\0\0"
    "showPersonOfGroup\0showCreateGeoupsWidget\0"
    "showGroupListInfo\0showDeleteOfGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserGroup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    2,   42,    2, 0x0a /* Public */,
       6,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void UserGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showGroupSummaryWidget(); break;
        case 1: _t->showPersonOfGroup(); break;
        case 2: _t->showCreateGeoupsWidget(); break;
        case 3: _t->showGroupListInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->showDeleteOfGroup(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserGroup::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_UserGroup.data,
    qt_meta_data_UserGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserGroup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
