/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../textedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DocEditor_t {
    QByteArrayData data[6];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DocEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DocEditor_t qt_meta_stringdata_DocEditor = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DocEditor"
QT_MOC_LITERAL(1, 10, 9), // "Newdatain"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "doc_netready"
QT_MOC_LITERAL(4, 34, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 49, 3) // "rep"

    },
    "DocEditor\0Newdatain\0\0doc_netready\0"
    "QNetworkReply*\0rep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DocEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void DocEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DocEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Newdatain(); break;
        case 1: _t->doc_netready((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DocEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DocEditor::Newdatain)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DocEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_DocEditor.data,
    qt_meta_data_DocEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DocEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DocEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DocEditor.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int DocEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DocEditor::Newdatain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_TextEdit_t {
    QByteArrayData data[38];
    char stringdata0[388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextEdit_t qt_meta_stringdata_TextEdit = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TextEdit"
QT_MOC_LITERAL(1, 9, 14), // "saveToDBsignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "str"
QT_MOC_LITERAL(4, 29, 12), // "dbOpenRecord"
QT_MOC_LITERAL(5, 42, 4), // "data"
QT_MOC_LITERAL(6, 47, 13), // "CursorMargins"
QT_MOC_LITERAL(7, 61, 4), // "left"
QT_MOC_LITERAL(8, 66, 5), // "right"
QT_MOC_LITERAL(9, 72, 7), // "fileNew"
QT_MOC_LITERAL(10, 80, 8), // "fileOpen"
QT_MOC_LITERAL(11, 89, 8), // "fileSave"
QT_MOC_LITERAL(12, 98, 8), // "saveToDB"
QT_MOC_LITERAL(13, 107, 10), // "fileSaveAs"
QT_MOC_LITERAL(14, 118, 9), // "filePrint"
QT_MOC_LITERAL(15, 128, 16), // "filePrintPreview"
QT_MOC_LITERAL(16, 145, 12), // "filePrintPdf"
QT_MOC_LITERAL(17, 158, 8), // "textBold"
QT_MOC_LITERAL(18, 167, 13), // "textUnderline"
QT_MOC_LITERAL(19, 181, 10), // "textItalic"
QT_MOC_LITERAL(20, 192, 10), // "textFamily"
QT_MOC_LITERAL(21, 203, 1), // "f"
QT_MOC_LITERAL(22, 205, 8), // "textSize"
QT_MOC_LITERAL(23, 214, 1), // "p"
QT_MOC_LITERAL(24, 216, 9), // "textStyle"
QT_MOC_LITERAL(25, 226, 10), // "styleIndex"
QT_MOC_LITERAL(26, 237, 9), // "textColor"
QT_MOC_LITERAL(27, 247, 9), // "textAlign"
QT_MOC_LITERAL(28, 257, 8), // "QAction*"
QT_MOC_LITERAL(29, 266, 1), // "a"
QT_MOC_LITERAL(30, 268, 24), // "currentCharFormatChanged"
QT_MOC_LITERAL(31, 293, 15), // "QTextCharFormat"
QT_MOC_LITERAL(32, 309, 6), // "format"
QT_MOC_LITERAL(33, 316, 21), // "cursorPositionChanged"
QT_MOC_LITERAL(34, 338, 20), // "clipboardDataChanged"
QT_MOC_LITERAL(35, 359, 5), // "about"
QT_MOC_LITERAL(36, 365, 12), // "printPreview"
QT_MOC_LITERAL(37, 378, 9) // "QPrinter*"

    },
    "TextEdit\0saveToDBsignal\0\0str\0dbOpenRecord\0"
    "data\0CursorMargins\0left\0right\0fileNew\0"
    "fileOpen\0fileSave\0saveToDB\0fileSaveAs\0"
    "filePrint\0filePrintPreview\0filePrintPdf\0"
    "textBold\0textUnderline\0textItalic\0"
    "textFamily\0f\0textSize\0p\0textStyle\0"
    "styleIndex\0textColor\0textAlign\0QAction*\0"
    "a\0currentCharFormatChanged\0QTextCharFormat\0"
    "format\0cursorPositionChanged\0"
    "clipboardDataChanged\0about\0printPreview\0"
    "QPrinter*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  137,    2, 0x0a /* Public */,
       6,    2,  140,    2, 0x08 /* Private */,
       9,    0,  145,    2, 0x08 /* Private */,
      10,    0,  146,    2, 0x08 /* Private */,
      11,    0,  147,    2, 0x08 /* Private */,
      12,    0,  148,    2, 0x08 /* Private */,
      13,    0,  149,    2, 0x08 /* Private */,
      14,    0,  150,    2, 0x08 /* Private */,
      15,    0,  151,    2, 0x08 /* Private */,
      16,    0,  152,    2, 0x08 /* Private */,
      17,    0,  153,    2, 0x08 /* Private */,
      18,    0,  154,    2, 0x08 /* Private */,
      19,    0,  155,    2, 0x08 /* Private */,
      20,    1,  156,    2, 0x08 /* Private */,
      22,    1,  159,    2, 0x08 /* Private */,
      24,    1,  162,    2, 0x08 /* Private */,
      26,    0,  165,    2, 0x08 /* Private */,
      27,    1,  166,    2, 0x08 /* Private */,
      30,    1,  169,    2, 0x08 /* Private */,
      33,    0,  172,    2, 0x08 /* Private */,
      34,    0,  173,    2, 0x08 /* Private */,
      35,    0,  174,    2, 0x08 /* Private */,
      36,    1,  175,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Bool, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 37,    2,

       0        // eod
};

void TextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveToDBsignal((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: { bool _r = _t->dbOpenRecord((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->CursorMargins((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 3: _t->fileNew(); break;
        case 4: _t->fileOpen(); break;
        case 5: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->saveToDB();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->filePrint(); break;
        case 9: _t->filePrintPreview(); break;
        case 10: _t->filePrintPdf(); break;
        case 11: _t->textBold(); break;
        case 12: _t->textUnderline(); break;
        case 13: _t->textItalic(); break;
        case 14: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->textColor(); break;
        case 18: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 19: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 20: _t->cursorPositionChanged(); break;
        case 21: _t->clipboardDataChanged(); break;
        case 22: _t->about(); break;
        case 23: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextEdit::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextEdit::saveToDBsignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TextEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_TextEdit.data,
    qt_meta_data_TextEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextEdit.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void TextEdit::saveToDBsignal(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
