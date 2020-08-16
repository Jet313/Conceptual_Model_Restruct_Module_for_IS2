/****************************************************************************
** Meta object code from reading C++ file 'QtClassLibrary1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtClassLibrary1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtClassLibrary1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyModuleForm_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyModuleForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyModuleForm_t qt_meta_stringdata_MyModuleForm = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyModuleForm"
QT_MOC_LITERAL(1, 13, 7), // "oneStep"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "allSteps"
QT_MOC_LITERAL(4, 31, 19), // "deleteCreatedTables"
QT_MOC_LITERAL(5, 51, 16) // "createItemTables"

    },
    "MyModuleForm\0oneStep\0\0allSteps\0"
    "deleteCreatedTables\0createItemTables"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyModuleForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyModuleForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyModuleForm *_t = static_cast<MyModuleForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->oneStep(); break;
        case 1: _t->allSteps(); break;
        case 2: _t->deleteCreatedTables(); break;
        case 3: _t->createItemTables(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyModuleForm::staticMetaObject = {
    { &WorkWidget::staticMetaObject, qt_meta_stringdata_MyModuleForm.data,
      qt_meta_data_MyModuleForm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyModuleForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyModuleForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyModuleForm.stringdata0))
        return static_cast<void*>(const_cast< MyModuleForm*>(this));
    return WorkWidget::qt_metacast(_clname);
}

int MyModuleForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WorkWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_MyHeader_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyHeader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyHeader_t qt_meta_stringdata_MyHeader = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyHeader"
QT_MOC_LITERAL(1, 9, 11), // "updateSizes"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12) // "updateOffset"

    },
    "MyHeader\0updateSizes\0\0updateOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyHeader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyHeader *_t = static_cast<MyHeader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSizes(); break;
        case 1: _t->updateOffset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyHeader::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_MyHeader.data,
      qt_meta_data_MyHeader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyHeader.stringdata0))
        return static_cast<void*>(const_cast< MyHeader*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int MyHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
