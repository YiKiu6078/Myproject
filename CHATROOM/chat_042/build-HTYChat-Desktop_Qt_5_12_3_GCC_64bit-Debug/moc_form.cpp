/****************************************************************************
** Meta object code from reading C++ file 'form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HTYChat/form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Form_t {
    QByteArrayData data[16];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Form_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Form_t qt_meta_stringdata_Form = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Form"
QT_MOC_LITERAL(1, 5, 29), // "on_pushButtonHomepage_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 25), // "on_pushButtonMenu_clicked"
QT_MOC_LITERAL(4, 62, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(5, 87, 8), // "showMenu"
QT_MOC_LITERAL(6, 96, 5), // "point"
QT_MOC_LITERAL(7, 102, 6), // "logout"
QT_MOC_LITERAL(8, 109, 5), // "about"
QT_MOC_LITERAL(9, 115, 4), // "lock"
QT_MOC_LITERAL(10, 120, 4), // "chat"
QT_MOC_LITERAL(11, 125, 3), // "row"
QT_MOC_LITERAL(12, 129, 6), // "column"
QT_MOC_LITERAL(13, 136, 7), // "profile"
QT_MOC_LITERAL(14, 144, 13), // "TWContextMenu"
QT_MOC_LITERAL(15, 158, 8) // "position"

    },
    "Form\0on_pushButtonHomepage_clicked\0\0"
    "on_pushButtonMenu_clicked\0"
    "on_pushButtonAdd_clicked\0showMenu\0"
    "point\0logout\0about\0lock\0chat\0row\0"
    "column\0profile\0TWContextMenu\0position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    2,   73,    2, 0x08 /* Private */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   15,

       0        // eod
};

void Form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Form *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonHomepage_clicked(); break;
        case 1: _t->on_pushButtonMenu_clicked(); break;
        case 2: _t->on_pushButtonAdd_clicked(); break;
        case 3: _t->showMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->logout(); break;
        case 5: _t->about(); break;
        case 6: _t->lock(); break;
        case 7: _t->chat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->profile(); break;
        case 9: _t->TWContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Form::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Form.data,
    qt_meta_data_Form,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Form.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
