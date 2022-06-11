/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../M4N3D_app/inc/mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
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
QT_MOC_LITERAL(1, 11, 11), // "stateUpdate"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "MSG"
QT_MOC_LITERAL(4, 28, 4), // "msgs"
QT_MOC_LITERAL(5, 33, 11), // "dataArrived"
QT_MOC_LITERAL(6, 45, 12), // "handleSearch"
QT_MOC_LITERAL(7, 58, 13), // "handleConnect"
QT_MOC_LITERAL(8, 72, 16), // "handleDisconnect"
QT_MOC_LITERAL(9, 89, 9), // "handleRun"
QT_MOC_LITERAL(10, 99, 10), // "handleStop"
QT_MOC_LITERAL(11, 110, 16), // "updateDataStatus"
QT_MOC_LITERAL(12, 127, 10), // "handleOpen"
QT_MOC_LITERAL(13, 138, 10), // "handleSave"
QT_MOC_LITERAL(14, 149, 8), // "showHelp"
QT_MOC_LITERAL(15, 158, 9), // "addToLogs"
QT_MOC_LITERAL(16, 168, 7), // "message"
QT_MOC_LITERAL(17, 176, 5), // "error"
QT_MOC_LITERAL(18, 182, 14), // "readFromDevice"
QT_MOC_LITERAL(19, 197, 10), // "runChecker"
QT_MOC_LITERAL(20, 208, 16), // "parseFrameBuffer"
QT_MOC_LITERAL(21, 225, 12), // "parseCommand"
QT_MOC_LITERAL(22, 238, 16), // "execInstructions"
QT_MOC_LITERAL(23, 255, 3), // "msg"
QT_MOC_LITERAL(24, 259, 10), // "sendPacket"
QT_MOC_LITERAL(25, 270, 4), // "data"
QT_MOC_LITERAL(26, 275, 14), // "highlightReset"
QT_MOC_LITERAL(27, 290, 17), // "highlightCodeLine"
QT_MOC_LITERAL(28, 308, 4) // "line"

    },
    "MainWindow\0stateUpdate\0\0MSG\0msgs\0"
    "dataArrived\0handleSearch\0handleConnect\0"
    "handleDisconnect\0handleRun\0handleStop\0"
    "updateDataStatus\0handleOpen\0handleSave\0"
    "showHelp\0addToLogs\0message\0error\0"
    "readFromDevice\0runChecker\0parseFrameBuffer\0"
    "parseCommand\0execInstructions\0msg\0"
    "sendPacket\0data\0highlightReset\0"
    "highlightCodeLine\0line"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       5,    0,  122,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  123,    2, 0x08 /* Private */,
       7,    0,  124,    2, 0x08 /* Private */,
       8,    0,  125,    2, 0x08 /* Private */,
       9,    0,  126,    2, 0x08 /* Private */,
      10,    0,  127,    2, 0x08 /* Private */,
      11,    0,  128,    2, 0x08 /* Private */,
      12,    0,  129,    2, 0x08 /* Private */,
      13,    0,  130,    2, 0x08 /* Private */,
      14,    0,  131,    2, 0x08 /* Private */,
      15,    2,  132,    2, 0x08 /* Private */,
      15,    1,  137,    2, 0x28 /* Private | MethodCloned */,
      18,    0,  140,    2, 0x08 /* Private */,
      19,    0,  141,    2, 0x08 /* Private */,
      20,    0,  142,    2, 0x08 /* Private */,
      21,    0,  143,    2, 0x08 /* Private */,
      22,    1,  144,    2, 0x08 /* Private */,
      24,    1,  147,    2, 0x08 /* Private */,
      26,    0,  150,    2, 0x08 /* Private */,
      27,    1,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   23,
    QMetaType::Void, QMetaType::QByteArray,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   28,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateUpdate((*reinterpret_cast< MSG(*)>(_a[1]))); break;
        case 1: _t->dataArrived(); break;
        case 2: _t->handleSearch(); break;
        case 3: _t->handleConnect(); break;
        case 4: _t->handleDisconnect(); break;
        case 5: _t->handleRun(); break;
        case 6: _t->handleStop(); break;
        case 7: _t->updateDataStatus(); break;
        case 8: _t->handleOpen(); break;
        case 9: _t->handleSave(); break;
        case 10: _t->showHelp(); break;
        case 11: _t->addToLogs((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->addToLogs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->readFromDevice(); break;
        case 14: { int _r = _t->runChecker();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->parseFrameBuffer(); break;
        case 16: _t->parseCommand(); break;
        case 17: _t->execInstructions((*reinterpret_cast< MSG(*)>(_a[1]))); break;
        case 18: _t->sendPacket((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 19: _t->highlightReset(); break;
        case 20: _t->highlightCodeLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(MSG );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stateUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::dataArrived)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::stateUpdate(MSG _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::dataArrived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
