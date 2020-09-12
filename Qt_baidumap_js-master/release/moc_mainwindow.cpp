/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "waypoints"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "obstacle_road"
QT_MOC_LITERAL(4, 36, 7), // "setflag"
QT_MOC_LITERAL(5, 44, 9), // "GpsUpdate"
QT_MOC_LITERAL(6, 54, 9), // "longitude"
QT_MOC_LITERAL(7, 64, 8), // "latitude"
QT_MOC_LITERAL(8, 73, 8), // "json_arr"
QT_MOC_LITERAL(9, 82, 9), // "revsecond"
QT_MOC_LITERAL(10, 92, 8), // "revthird"
QT_MOC_LITERAL(11, 101, 10), // "longitude1"
QT_MOC_LITERAL(12, 112, 9), // "latitude1"
QT_MOC_LITERAL(13, 122, 14), // "onGpsClientRun"
QT_MOC_LITERAL(14, 137, 14), // "onPathPlanning"
QT_MOC_LITERAL(15, 152, 18), // "onExitPathPlanning"
QT_MOC_LITERAL(16, 171, 24), // "onTcpServerButtonClicked"
QT_MOC_LITERAL(17, 196, 24), // "onTcpServerNewConnection"
QT_MOC_LITERAL(18, 221, 4), // "from"
QT_MOC_LITERAL(19, 226, 4), // "port"
QT_MOC_LITERAL(20, 231, 28), // "onTcpServerStopButtonClicked"
QT_MOC_LITERAL(21, 260, 34), // "onTcpServerDisconnectButtonCl..."
QT_MOC_LITERAL(22, 295, 23), // "onTcpServerDisconnected"
QT_MOC_LITERAL(23, 319, 22), // "onTcpServerSendMessage"
QT_MOC_LITERAL(24, 342, 14), // "getcoordinates"
QT_MOC_LITERAL(25, 357, 3), // "lon"
QT_MOC_LITERAL(26, 361, 3), // "lat"
QT_MOC_LITERAL(27, 365, 15), // "returnWayPoints"
QT_MOC_LITERAL(28, 381, 11) // "r_waypoints"

    },
    "MainWindow\0waypoints\0\0obstacle_road\0"
    "setflag\0GpsUpdate\0longitude\0latitude\0"
    "json_arr\0revsecond\0revthird\0longitude1\0"
    "latitude1\0onGpsClientRun\0onPathPlanning\0"
    "onExitPathPlanning\0onTcpServerButtonClicked\0"
    "onTcpServerNewConnection\0from\0port\0"
    "onTcpServerStopButtonClicked\0"
    "onTcpServerDisconnectButtonClicked\0"
    "onTcpServerDisconnected\0onTcpServerSendMessage\0"
    "getcoordinates\0lon\0lat\0returnWayPoints\0"
    "r_waypoints"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    4,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  101,    2, 0x08 /* Private */,
       5,    7,  104,    2, 0x08 /* Private */,
      13,    0,  119,    2, 0x08 /* Private */,
      14,    0,  120,    2, 0x08 /* Private */,
      15,    0,  121,    2, 0x08 /* Private */,
      16,    0,  122,    2, 0x08 /* Private */,
      17,    2,  123,    2, 0x08 /* Private */,
      20,    0,  128,    2, 0x08 /* Private */,
      21,    0,  129,    2, 0x08 /* Private */,
      22,    0,  130,    2, 0x08 /* Private */,
      23,    0,  131,    2, 0x08 /* Private */,
      24,    2,  132,    2, 0x0a /* Public */,
      27,    1,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QJsonArray, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   25,   26,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->waypoints((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->obstacle_road((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: _t->setflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->GpsUpdate((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QJsonArray(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7]))); break;
        case 4: _t->onGpsClientRun(); break;
        case 5: _t->onPathPlanning(); break;
        case 6: _t->onExitPathPlanning(); break;
        case 7: _t->onTcpServerButtonClicked(); break;
        case 8: _t->onTcpServerNewConnection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 9: _t->onTcpServerStopButtonClicked(); break;
        case 10: _t->onTcpServerDisconnectButtonClicked(); break;
        case 11: _t->onTcpServerDisconnected(); break;
        case 12: _t->onTcpServerSendMessage(); break;
        case 13: _t->getcoordinates((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 14: _t->returnWayPoints((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::waypoints)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QString , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::obstacle_road)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::waypoints(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::obstacle_road(QString _t1, QString _t2, double _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
