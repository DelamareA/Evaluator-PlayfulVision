/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Evaluator-PlayfulVision/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "displayVideoError"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "QMediaPlayer::Error"
QT_MOC_LITERAL(4, 50, 5), // "error"
QT_MOC_LITERAL(5, 56, 22), // "slotMediaStatusChanged"
QT_MOC_LITERAL(6, 79, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(7, 105, 5), // "state"
QT_MOC_LITERAL(8, 111, 19), // "slotdurationChanged"
QT_MOC_LITERAL(9, 131, 8), // "duration"
QT_MOC_LITERAL(10, 140, 6), // "update"
QT_MOC_LITERAL(11, 147, 13), // "slotNextFrame"
QT_MOC_LITERAL(12, 161, 26), // "slotActionLoadNumTriggered"
QT_MOC_LITERAL(13, 188, 28), // "slotActionLoadColorTriggered"
QT_MOC_LITERAL(14, 217, 25), // "slotSpinInputValueChanged"
QT_MOC_LITERAL(15, 243, 26), // "slotComboInputIndexChanged"
QT_MOC_LITERAL(16, 270, 26), // "slotCheckInputStateChanged"
QT_MOC_LITERAL(17, 297, 15) // "slotSaveAndExit"

    },
    "MainWindow\0displayVideoError\0\0"
    "QMediaPlayer::Error\0error\0"
    "slotMediaStatusChanged\0QMediaPlayer::MediaStatus\0"
    "state\0slotdurationChanged\0duration\0"
    "update\0slotNextFrame\0slotActionLoadNumTriggered\0"
    "slotActionLoadColorTriggered\0"
    "slotSpinInputValueChanged\0"
    "slotComboInputIndexChanged\0"
    "slotCheckInputStateChanged\0slotSaveAndExit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       5,    1,   72,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x08 /* Private */,
      10,    0,   78,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      13,    1,   83,    2, 0x08 /* Private */,
      14,    1,   86,    2, 0x08 /* Private */,
      15,    1,   89,    2, 0x08 /* Private */,
      16,    1,   92,    2, 0x08 /* Private */,
      17,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::LongLong,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayVideoError((*reinterpret_cast< QMediaPlayer::Error(*)>(_a[1]))); break;
        case 1: _t->slotMediaStatusChanged((*reinterpret_cast< QMediaPlayer::MediaStatus(*)>(_a[1]))); break;
        case 2: _t->slotdurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->update(); break;
        case 4: _t->slotNextFrame(); break;
        case 5: _t->slotActionLoadNumTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slotActionLoadColorTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slotSpinInputValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotComboInputIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotCheckInputStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotSaveAndExit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::Error >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::MediaStatus >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
