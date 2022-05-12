/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../code source/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[18];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 18), // "si_sendSelectedVar"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "si_quitApp"
QT_MOC_LITERAL(4, 38, 10), // "si_isAndOr"
QT_MOC_LITERAL(5, 49, 16), // "si_isAllSelected"
QT_MOC_LITERAL(6, 66, 13), // "sl_getListVar"
QT_MOC_LITERAL(7, 80, 4), // "list"
QT_MOC_LITERAL(8, 85, 17), // "sl_getNewRuleOrga"
QT_MOC_LITERAL(9, 103, 16), // "sl_getRuleFilled"
QT_MOC_LITERAL(10, 120, 12), // "ruleSelected"
QT_MOC_LITERAL(11, 133, 8), // "t_option"
QT_MOC_LITERAL(12, 142, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(13, 164, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(14, 186, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(15, 208, 18), // "on_addRule_clicked"
QT_MOC_LITERAL(16, 227, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(17, 249, 19) // "on_Dialog_destroyed"

    },
    "Dialog\0si_sendSelectedVar\0\0si_quitApp\0"
    "si_isAndOr\0si_isAllSelected\0sl_getListVar\0"
    "list\0sl_getNewRuleOrga\0sl_getRuleFilled\0"
    "ruleSelected\0t_option\0on_buttonBox_accepted\0"
    "on_pushButton_clicked\0on_buttonBox_rejected\0"
    "on_addRule_clicked\0on_toolButton_clicked\0"
    "on_Dialog_destroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    0,   82,    2, 0x06 /* Public */,
       4,    1,   83,    2, 0x06 /* Public */,
       5,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   89,    2, 0x08 /* Private */,
       8,    1,   92,    2, 0x08 /* Private */,
       9,    3,   95,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    0,  106,    2, 0x08 /* Private */,
      17,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10, 0x80000000 | 11,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->si_sendSelectedVar((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->si_quitApp(); break;
        case 2: _t->si_isAndOr((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->si_isAllSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->sl_getListVar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sl_getNewRuleOrga((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sl_getRuleFilled((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< ruleSelected(*)>(_a[2])),(*reinterpret_cast< t_option(*)>(_a[3]))); break;
        case 7: _t->on_buttonBox_accepted(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->on_buttonBox_rejected(); break;
        case 10: _t->on_addRule_clicked(); break;
        case 11: _t->on_toolButton_clicked(); break;
        case 12: _t->on_Dialog_destroyed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog::si_sendSelectedVar)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog::si_quitApp)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Dialog::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog::si_isAndOr)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Dialog::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog::si_isAllSelected)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialog.data,
    qt_meta_data_Dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Dialog::si_sendSelectedVar(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog::si_quitApp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Dialog::si_isAndOr(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Dialog::si_isAllSelected(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
