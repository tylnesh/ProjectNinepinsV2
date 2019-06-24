/****************************************************************************
** Meta object code from reading C++ file 'gamewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ninepins_rpi_1.2/gamewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameWindow_t {
    QByteArrayData data[19];
    char stringdata0[284];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameWindow_t qt_meta_stringdata_GameWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameWindow"
QT_MOC_LITERAL(1, 11, 7), // "sendMsg"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "Status*"
QT_MOC_LITERAL(4, 28, 3), // "msg"
QT_MOC_LITERAL(5, 32, 15), // "on_pin1_clicked"
QT_MOC_LITERAL(6, 48, 15), // "on_pin2_clicked"
QT_MOC_LITERAL(7, 64, 15), // "on_pin3_clicked"
QT_MOC_LITERAL(8, 80, 15), // "on_pin4_clicked"
QT_MOC_LITERAL(9, 96, 15), // "on_pin5_clicked"
QT_MOC_LITERAL(10, 112, 15), // "on_pin6_clicked"
QT_MOC_LITERAL(11, 128, 15), // "on_pin7_clicked"
QT_MOC_LITERAL(12, 144, 15), // "on_pin8_clicked"
QT_MOC_LITERAL(13, 160, 15), // "on_pin0_clicked"
QT_MOC_LITERAL(14, 176, 28), // "on_changeStateButton_clicked"
QT_MOC_LITERAL(15, 205, 28), // "on_settingPinsButton_clicked"
QT_MOC_LITERAL(16, 234, 24), // "on_endGameButton_clicked"
QT_MOC_LITERAL(17, 259, 11), // "onRedrawGUI"
QT_MOC_LITERAL(18, 271, 12) // "onCheckGaffe"

    },
    "GameWindow\0sendMsg\0\0Status*\0msg\0"
    "on_pin1_clicked\0on_pin2_clicked\0"
    "on_pin3_clicked\0on_pin4_clicked\0"
    "on_pin5_clicked\0on_pin6_clicked\0"
    "on_pin7_clicked\0on_pin8_clicked\0"
    "on_pin0_clicked\0on_changeStateButton_clicked\0"
    "on_settingPinsButton_clicked\0"
    "on_endGameButton_clicked\0onRedrawGUI\0"
    "onCheckGaffe"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMsg((*reinterpret_cast< Status*(*)>(_a[1]))); break;
        case 1: _t->on_pin1_clicked(); break;
        case 2: _t->on_pin2_clicked(); break;
        case 3: _t->on_pin3_clicked(); break;
        case 4: _t->on_pin4_clicked(); break;
        case 5: _t->on_pin5_clicked(); break;
        case 6: _t->on_pin6_clicked(); break;
        case 7: _t->on_pin7_clicked(); break;
        case 8: _t->on_pin8_clicked(); break;
        case 9: _t->on_pin0_clicked(); break;
        case 10: _t->on_changeStateButton_clicked(); break;
        case 11: _t->on_settingPinsButton_clicked(); break;
        case 12: _t->on_endGameButton_clicked(); break;
        case 13: _t->onRedrawGUI(); break;
        case 14: _t->onCheckGaffe(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameWindow::*)(Status * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameWindow::sendMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameWindow::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_GameWindow.data,
    qt_meta_data_GameWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void GameWindow::sendMsg(Status * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
