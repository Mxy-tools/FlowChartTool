/****************************************************************************
** Meta object code from reading C++ file 'flowchart_graphics_item.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../flowchart_graphics_item.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flowchart_graphics_item.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_FlowchartGraphicsRectItem_t {
    uint offsetsAndSizes[2];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowchartGraphicsRectItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowchartGraphicsRectItem_t qt_meta_stringdata_FlowchartGraphicsRectItem = {
    {
        QT_MOC_LITERAL(0, 25)   // "FlowchartGraphicsRectItem"
    },
    "FlowchartGraphicsRectItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowchartGraphicsRectItem[] = {

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

Q_CONSTINIT const QMetaObject FlowchartGraphicsRectItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FlowchartGraphicsRectItem.offsetsAndSizes,
    qt_meta_data_FlowchartGraphicsRectItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowchartGraphicsRectItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowchartGraphicsRectItem, std::true_type>
    >,
    nullptr
} };

void FlowchartGraphicsRectItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *FlowchartGraphicsRectItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowchartGraphicsRectItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowchartGraphicsRectItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(this);
    if (!strcmp(_clname, "FlowchartGraphicsItem"))
        return static_cast< FlowchartGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int FlowchartGraphicsRectItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_FlowchartGraphicsConditionItem_t {
    uint offsetsAndSizes[2];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowchartGraphicsConditionItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowchartGraphicsConditionItem_t qt_meta_stringdata_FlowchartGraphicsConditionItem = {
    {
        QT_MOC_LITERAL(0, 30)   // "FlowchartGraphicsConditionItem"
    },
    "FlowchartGraphicsConditionItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowchartGraphicsConditionItem[] = {

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

Q_CONSTINIT const QMetaObject FlowchartGraphicsConditionItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FlowchartGraphicsConditionItem.offsetsAndSizes,
    qt_meta_data_FlowchartGraphicsConditionItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowchartGraphicsConditionItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowchartGraphicsConditionItem, std::true_type>
    >,
    nullptr
} };

void FlowchartGraphicsConditionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *FlowchartGraphicsConditionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowchartGraphicsConditionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowchartGraphicsConditionItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    if (!strcmp(_clname, "FlowchartGraphicsItem"))
        return static_cast< FlowchartGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int FlowchartGraphicsConditionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_FlowchartGraphicsCirculationItem_t {
    uint offsetsAndSizes[2];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FlowchartGraphicsCirculationItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FlowchartGraphicsCirculationItem_t qt_meta_stringdata_FlowchartGraphicsCirculationItem = {
    {
        QT_MOC_LITERAL(0, 32)   // "FlowchartGraphicsCirculationItem"
    },
    "FlowchartGraphicsCirculationItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FlowchartGraphicsCirculationItem[] = {

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

Q_CONSTINIT const QMetaObject FlowchartGraphicsCirculationItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FlowchartGraphicsCirculationItem.offsetsAndSizes,
    qt_meta_data_FlowchartGraphicsCirculationItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FlowchartGraphicsCirculationItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FlowchartGraphicsCirculationItem, std::true_type>
    >,
    nullptr
} };

void FlowchartGraphicsCirculationItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *FlowchartGraphicsCirculationItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowchartGraphicsCirculationItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowchartGraphicsCirculationItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    if (!strcmp(_clname, "FlowchartGraphicsItem"))
        return static_cast< FlowchartGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int FlowchartGraphicsCirculationItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
