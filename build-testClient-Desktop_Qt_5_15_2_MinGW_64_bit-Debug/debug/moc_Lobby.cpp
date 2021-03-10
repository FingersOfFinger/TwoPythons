/****************************************************************************
** Meta object code from reading C++ file 'Lobby.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../testClientTwoPythons-main/Lobby.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Lobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Lobby_t {
    QByteArrayData data[19];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lobby_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lobby_t qt_meta_stringdata_Lobby = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Lobby"
QT_MOC_LITERAL(1, 6, 12), // "receiveLobby"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "sockDisc"
QT_MOC_LITERAL(4, 29, 10), // "enterLobby"
QT_MOC_LITERAL(5, 40, 17), // "receiveEnterLobby"
QT_MOC_LITERAL(6, 58, 11), // "createLobby"
QT_MOC_LITERAL(7, 70, 18), // "receiveCreateLobby"
QT_MOC_LITERAL(8, 89, 9), // "exitLobby"
QT_MOC_LITERAL(9, 99, 16), // "receiveExitLobby"
QT_MOC_LITERAL(10, 116, 11), // "deleteLobby"
QT_MOC_LITERAL(11, 128, 18), // "receiveDeleteLobby"
QT_MOC_LITERAL(12, 147, 12), // "refreshLobby"
QT_MOC_LITERAL(13, 160, 15), // "receiveGetLobby"
QT_MOC_LITERAL(14, 176, 8), // "statGame"
QT_MOC_LITERAL(15, 185, 15), // "receiveStatGame"
QT_MOC_LITERAL(16, 201, 9), // "startGame"
QT_MOC_LITERAL(17, 211, 16), // "receiveStartGame"
QT_MOC_LITERAL(18, 228, 4) // "exit"

    },
    "Lobby\0receiveLobby\0\0sockDisc\0enterLobby\0"
    "receiveEnterLobby\0createLobby\0"
    "receiveCreateLobby\0exitLobby\0"
    "receiveExitLobby\0deleteLobby\0"
    "receiveDeleteLobby\0refreshLobby\0"
    "receiveGetLobby\0statGame\0receiveStatGame\0"
    "startGame\0receiveStartGame\0exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lobby[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x0a /* Public */,
       3,    0,  100,    2, 0x0a /* Public */,
       4,    0,  101,    2, 0x0a /* Public */,
       5,    0,  102,    2, 0x0a /* Public */,
       6,    0,  103,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    0,  107,    2, 0x0a /* Public */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    0,  111,    2, 0x0a /* Public */,
      15,    0,  112,    2, 0x0a /* Public */,
      16,    0,  113,    2, 0x0a /* Public */,
      17,    0,  114,    2, 0x0a /* Public */,
      18,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void Lobby::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Lobby *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveLobby(); break;
        case 1: _t->sockDisc(); break;
        case 2: _t->enterLobby(); break;
        case 3: { bool _r = _t->receiveEnterLobby();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->createLobby(); break;
        case 5: { bool _r = _t->receiveCreateLobby();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->exitLobby(); break;
        case 7: { bool _r = _t->receiveExitLobby();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->deleteLobby(); break;
        case 9: { bool _r = _t->receiveDeleteLobby();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->refreshLobby(); break;
        case 11: _t->receiveGetLobby(); break;
        case 12: _t->statGame(); break;
        case 13: _t->receiveStatGame(); break;
        case 14: _t->startGame(); break;
        case 15: { bool _r = _t->receiveStartGame();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->exit(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Lobby::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Lobby.data,
    qt_meta_data_Lobby,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Lobby::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lobby::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lobby.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Lobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
