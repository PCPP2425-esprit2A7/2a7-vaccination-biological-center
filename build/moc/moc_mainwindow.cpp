/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "envoyerEmailAvecInfos",
    "",
    "email",
    "body",
    "on_ajouter_clicked",
    "on_deleteb_clicked",
    "on_tableWidget_cellDoubleClicked",
    "row",
    "column",
    "on_cancelButton_clicked",
    "on_rechb_clicked",
    "on_rech_textChanged",
    "searchText",
    "on_sortComboBox_changed",
    "sortType",
    "on_loginButton_clicked",
    "on_pushButton_8_clicked",
    "on_pdfb_clicked",
    "handleRFID",
    "uid"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   86,    2, 0x0a,    1 /* Public */,
       5,    0,   91,    2, 0x08,    4 /* Private */,
       6,    0,   92,    2, 0x08,    5 /* Private */,
       7,    2,   93,    2, 0x08,    6 /* Private */,
      10,    0,   98,    2, 0x08,    9 /* Private */,
      11,    0,   99,    2, 0x08,   10 /* Private */,
      12,    1,  100,    2, 0x08,   11 /* Private */,
      14,    1,  103,    2, 0x08,   13 /* Private */,
      16,    0,  106,    2, 0x08,   15 /* Private */,
      17,    0,  107,    2, 0x08,   16 /* Private */,
      18,    0,  108,    2, 0x08,   17 /* Private */,
      19,    1,  109,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'envoyerEmailAvecInfos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_ajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_cellDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_cancelButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rechb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rech_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_sortComboBox_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_loginButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_8_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pdfb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleRFID'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->envoyerEmailAvecInfos((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->on_ajouter_clicked(); break;
        case 2: _t->on_deleteb_clicked(); break;
        case 3: _t->on_tableWidget_cellDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->on_cancelButton_clicked(); break;
        case 5: _t->on_rechb_clicked(); break;
        case 6: _t->on_rech_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_sortComboBox_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->on_loginButton_clicked(); break;
        case 9: _t->on_pushButton_8_clicked(); break;
        case 10: _t->on_pdfb_clicked(); break;
        case 11: _t->handleRFID((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
