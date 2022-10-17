/****************************************************************************
** Meta object code from reading C++ file 'flowchar_widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../flowchar_widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flowchar_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_FlowCharWidget_t {
    uint offsetsAndSizes[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowCharWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowCharWidget_t qt_meta_stringdata_FlowCharWidget = {
    {
        QT_MOC_LITERAL(0, 14)   // "FlowCharWidget"
    },
    "FlowCharWidget"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowCharWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject FlowCharWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_FlowCharWidget.offsetsAndSizes,
    qt_meta_data_FlowCharWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowCharWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowCharWidget, std::true_type>
    >,
    nullptr
} };

void FlowCharWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *FlowCharWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowCharWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowCharWidget.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FlowCharWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_FlowCharToolButtonBar_t {
    uint offsetsAndSizes[6];
    char stringdata0[22];
    char stringdata1[15];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowCharToolButtonBar_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowCharToolButtonBar_t qt_meta_stringdata_FlowCharToolButtonBar = {
    {
        QT_MOC_LITERAL(0, 21),  // "FlowCharToolButtonBar"
        QT_MOC_LITERAL(22, 14),  // "FlowActionSlot"
        QT_MOC_LITERAL(37, 0)   // ""
    },
    "FlowCharToolButtonBar",
    "FlowActionSlot",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowCharToolButtonBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FlowCharToolButtonBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QToolBar::staticMetaObject>(),
    qt_meta_stringdata_FlowCharToolButtonBar.offsetsAndSizes,
    qt_meta_data_FlowCharToolButtonBar,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowCharToolButtonBar_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowCharToolButtonBar, std::true_type>,
        // method 'FlowActionSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FlowCharToolButtonBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlowCharToolButtonBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FlowActionSlot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *FlowCharToolButtonBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowCharToolButtonBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowCharToolButtonBar.stringdata0))
        return static_cast<void*>(this);
    return QToolBar::qt_metacast(_clname);
}

int FlowCharToolButtonBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_FlowCharToolSideBar_t {
    uint offsetsAndSizes[6];
    char stringdata0[20];
    char stringdata1[15];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowCharToolSideBar_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowCharToolSideBar_t qt_meta_stringdata_FlowCharToolSideBar = {
    {
        QT_MOC_LITERAL(0, 19),  // "FlowCharToolSideBar"
        QT_MOC_LITERAL(20, 14),  // "FlowButtonSlot"
        QT_MOC_LITERAL(35, 0)   // ""
    },
    "FlowCharToolSideBar",
    "FlowButtonSlot",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowCharToolSideBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FlowCharToolSideBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_FlowCharToolSideBar.offsetsAndSizes,
    qt_meta_data_FlowCharToolSideBar,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowCharToolSideBar_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowCharToolSideBar, std::true_type>,
        // method 'FlowButtonSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FlowCharToolSideBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlowCharToolSideBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FlowButtonSlot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *FlowCharToolSideBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowCharToolSideBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowCharToolSideBar.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int FlowCharToolSideBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
