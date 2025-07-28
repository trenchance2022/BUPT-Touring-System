/****************************************************************************
** Meta object code from reading C++ file 'mymap.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mymap.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSmyMapENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSmyMapENDCLASS = QtMocHelpers::stringData(
    "myMap",
    "quit_function",
    "",
    "on_backBtn_clicked",
    "on_routePlanBtn_clicked",
    "on_editRouteBtn_clicked",
    "on_facilitySearch_clicked",
    "on_foodSearch_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSmyMapENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[6];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[24];
    char stringdata5[24];
    char stringdata6[26];
    char stringdata7[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSmyMapENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSmyMapENDCLASS_t qt_meta_stringdata_CLASSmyMapENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "myMap"
        QT_MOC_LITERAL(6, 13),  // "quit_function"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 18),  // "on_backBtn_clicked"
        QT_MOC_LITERAL(40, 23),  // "on_routePlanBtn_clicked"
        QT_MOC_LITERAL(64, 23),  // "on_editRouteBtn_clicked"
        QT_MOC_LITERAL(88, 25),  // "on_facilitySearch_clicked"
        QT_MOC_LITERAL(114, 21)   // "on_foodSearch_clicked"
    },
    "myMap",
    "quit_function",
    "",
    "on_backBtn_clicked",
    "on_routePlanBtn_clicked",
    "on_editRouteBtn_clicked",
    "on_facilitySearch_clicked",
    "on_foodSearch_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSmyMapENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject myMap::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSmyMapENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSmyMapENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSmyMapENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<myMap, std::true_type>,
        // method 'quit_function'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_backBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_routePlanBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_editRouteBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_facilitySearch_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_foodSearch_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void myMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myMap *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->quit_function(); break;
        case 1: _t->on_backBtn_clicked(); break;
        case 2: _t->on_routePlanBtn_clicked(); break;
        case 3: _t->on_editRouteBtn_clicked(); break;
        case 4: _t->on_facilitySearch_clicked(); break;
        case 5: _t->on_foodSearch_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myMap::*)();
            if (_t _q_method = &myMap::quit_function; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *myMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSmyMapENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int myMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void myMap::quit_function()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
