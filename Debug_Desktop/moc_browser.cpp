/****************************************************************************
** Meta object code from reading C++ file 'browser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../browser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Browser_t {
    QByteArrayData data[20];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Browser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Browser_t qt_meta_stringdata_Browser = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Browser"
QT_MOC_LITERAL(1, 8, 13), // "addConnection"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "addItem"
QT_MOC_LITERAL(4, 31, 7), // "delItem"
QT_MOC_LITERAL(5, 39, 13), // "beginMoveItem"
QT_MOC_LITERAL(6, 53, 11), // "endMoveItem"
QT_MOC_LITERAL(7, 65, 9), // "QSqlError"
QT_MOC_LITERAL(8, 75, 6), // "driver"
QT_MOC_LITERAL(9, 82, 6), // "dbName"
QT_MOC_LITERAL(10, 89, 4), // "host"
QT_MOC_LITERAL(11, 94, 4), // "user"
QT_MOC_LITERAL(12, 99, 6), // "passwd"
QT_MOC_LITERAL(13, 106, 4), // "port"
QT_MOC_LITERAL(14, 111, 8), // "initTree"
QT_MOC_LITERAL(15, 120, 8), // "showText"
QT_MOC_LITERAL(16, 129, 11), // "QModelIndex"
QT_MOC_LITERAL(17, 141, 5), // "index"
QT_MOC_LITERAL(18, 147, 8), // "saveToDB"
QT_MOC_LITERAL(19, 156, 4) // "data"

    },
    "Browser\0addConnection\0\0addItem\0delItem\0"
    "beginMoveItem\0endMoveItem\0QSqlError\0"
    "driver\0dbName\0host\0user\0passwd\0port\0"
    "initTree\0showText\0QModelIndex\0index\0"
    "saveToDB\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Browser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       1,    6,   64,    2, 0x08 /* Private */,
      14,    0,   77,    2, 0x08 /* Private */,
      15,    1,   78,    2, 0x08 /* Private */,
      18,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 7, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    8,    9,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QByteArray,   19,

       0        // eod
};

void Browser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Browser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addConnection(); break;
        case 1: _t->addItem(); break;
        case 2: _t->delItem(); break;
        case 3: _t->beginMoveItem(); break;
        case 4: _t->endMoveItem(); break;
        case 5: { QSqlError _r = _t->addConnection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QSqlError*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->initTree(); break;
        case 7: _t->showText((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: _t->saveToDB((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Browser::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Browser.data,
    qt_meta_data_Browser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Browser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Browser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Browser.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
