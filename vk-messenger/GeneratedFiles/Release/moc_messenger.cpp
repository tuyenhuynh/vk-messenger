/****************************************************************************
** Meta object code from reading C++ file 'messenger.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../messenger.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messenger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Messenger[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   25,   10,   10, 0x08,
      58,   10,   10,   10, 0x08,
      75,   71,   10,   10, 0x08,
      90,   10,   10,   10, 0x08,
     109,   10,   10,   10, 0x08,
     123,   10,   10,   10, 0x08,
     149,   10,   10,   10, 0x08,
     157,   10,   10,   10, 0x08,
     186,  182,   10,   10, 0x08,
     223,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Messenger[] = {
    "Messenger\0\0authSuccess()\0,\0"
    "updateCurrentChatPeer(int,int)\0"
    "getFriends()\0url\0urlCheck(QUrl)\0"
    "afterAuthSuccess()\0sendMessage()\0"
    "loadImage(QNetworkReply*)\0print()\0"
    "displayRealtimeMessage()\0uid\0"
    "getUnreadMessagesFromFriend(QString)\0"
    "logout()\0"
};

void Messenger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Messenger *_t = static_cast<Messenger *>(_o);
        switch (_id) {
        case 0: _t->authSuccess(); break;
        case 1: _t->updateCurrentChatPeer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->getFriends(); break;
        case 3: _t->urlCheck((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 4: _t->afterAuthSuccess(); break;
        case 5: _t->sendMessage(); break;
        case 6: _t->loadImage((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->print(); break;
        case 8: _t->displayRealtimeMessage(); break;
        case 9: _t->getUnreadMessagesFromFriend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->logout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Messenger::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Messenger::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Messenger,
      qt_meta_data_Messenger, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Messenger::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Messenger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Messenger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Messenger))
        return static_cast<void*>(const_cast< Messenger*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Messenger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Messenger::authSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
