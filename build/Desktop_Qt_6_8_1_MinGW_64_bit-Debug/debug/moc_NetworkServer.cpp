/****************************************************************************
** Meta object code from reading C++ file 'NetworkServer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../NetworkServer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13NetworkServerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13NetworkServerE = QtMocHelpers::stringData(
    "NetworkServer",
    "clientDataReceived",
    "",
    "QTcpSocket*",
    "clientSocket",
    "data",
    "clientConnected",
    "ipAddress",
    "connectionStatusChanged",
    "connected",
    "errorOccurred",
    "error",
    "serverStopped",
    "stopServer",
    "onNewConnection",
    "onReadyRead",
    "onDisconnected",
    "checkConnections"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13NetworkServerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,
       6,    1,   79,    2, 0x06,    4 /* Public */,
       8,    1,   82,    2, 0x06,    6 /* Public */,
      10,    1,   85,    2, 0x06,    8 /* Public */,
      12,    0,   88,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,   89,    2, 0x0a,   11 /* Public */,
      14,    0,   90,    2, 0x08,   12 /* Private */,
      15,    0,   91,    2, 0x08,   13 /* Private */,
      16,    0,   92,    2, 0x08,   14 /* Private */,
      17,    0,   93,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject NetworkServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN13NetworkServerE.offsetsAndSizes,
    qt_meta_data_ZN13NetworkServerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13NetworkServerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NetworkServer, std::true_type>,
        // method 'clientDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'clientConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'connectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'serverStopped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNewConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkConnections'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NetworkServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clientDataReceived((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        case 1: _t->clientConnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->connectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->serverStopped(); break;
        case 5: _t->stopServer(); break;
        case 6: _t->onNewConnection(); break;
        case 7: _t->onReadyRead(); break;
        case 8: _t->onDisconnected(); break;
        case 9: _t->checkConnections(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (NetworkServer::*)(QTcpSocket * , const QByteArray & );
            if (_q_method_type _q_method = &NetworkServer::clientDataReceived; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (NetworkServer::*)(const QString & );
            if (_q_method_type _q_method = &NetworkServer::clientConnected; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (NetworkServer::*)(bool );
            if (_q_method_type _q_method = &NetworkServer::connectionStatusChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (NetworkServer::*)(const QString & );
            if (_q_method_type _q_method = &NetworkServer::errorOccurred; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (NetworkServer::*)();
            if (_q_method_type _q_method = &NetworkServer::serverStopped; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *NetworkServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13NetworkServerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void NetworkServer::clientDataReceived(QTcpSocket * _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkServer::clientConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkServer::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetworkServer::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NetworkServer::serverStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
