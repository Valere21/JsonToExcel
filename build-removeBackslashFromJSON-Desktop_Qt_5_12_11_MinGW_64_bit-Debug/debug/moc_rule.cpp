/****************************************************************************
** Meta object code from reading C++ file 'rule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../code source/rule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Rule_t {
    QByteArrayData data[18];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Rule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Rule_t qt_meta_stringdata_Rule = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Rule"
QT_MOC_LITERAL(1, 5, 17), // "si_sendRuleFilled"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "var"
QT_MOC_LITERAL(4, 28, 12), // "ruleSelected"
QT_MOC_LITERAL(5, 41, 4), // "rule"
QT_MOC_LITERAL(6, 46, 8), // "t_option"
QT_MOC_LITERAL(7, 55, 6), // "option"
QT_MOC_LITERAL(8, 62, 21), // "on_listRule_activated"
QT_MOC_LITERAL(9, 84, 5), // "index"
QT_MOC_LITERAL(10, 90, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(11, 112, 17), // "on_getVar_clicked"
QT_MOC_LITERAL(12, 130, 7), // "checked"
QT_MOC_LITERAL(13, 138, 19), // "on_getConst_clicked"
QT_MOC_LITERAL(14, 158, 30), // "on_listVar_currentIndexChanged"
QT_MOC_LITERAL(15, 189, 4), // "arg1"
QT_MOC_LITERAL(16, 194, 33), // "on_listVarRes_currentIndexCha..."
QT_MOC_LITERAL(17, 228, 24) // "on_constRes_valueChanged"

    },
    "Rule\0si_sendRuleFilled\0\0var\0ruleSelected\0"
    "rule\0t_option\0option\0on_listRule_activated\0"
    "index\0on_buttonBox_accepted\0"
    "on_getVar_clicked\0checked\0on_getConst_clicked\0"
    "on_listVar_currentIndexChanged\0arg1\0"
    "on_listVarRes_currentIndexChanged\0"
    "on_constRes_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Rule[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   61,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    1,   65,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      14,    1,   71,    2, 0x08 /* Private */,
      16,    1,   74,    2, 0x08 /* Private */,
      17,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Double,   15,

       0        // eod
};

void Rule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Rule *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->si_sendRuleFilled((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< ruleSelected(*)>(_a[2])),(*reinterpret_cast< t_option(*)>(_a[3]))); break;
        case 1: _t->on_listRule_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_buttonBox_accepted(); break;
        case 3: _t->on_getVar_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_getConst_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_listVar_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_listVarRes_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_constRes_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Rule::*)(QString , ruleSelected , t_option );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Rule::si_sendRuleFilled)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Rule::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Rule.data,
    qt_meta_data_Rule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Rule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Rule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Rule.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Rule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Rule::si_sendRuleFilled(QString _t1, ruleSelected _t2, t_option _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
