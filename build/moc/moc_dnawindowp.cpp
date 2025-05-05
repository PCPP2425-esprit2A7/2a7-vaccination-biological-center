/****************************************************************************
** Meta object code from reading C++ file 'dnawindowp.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dnawindowp.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dnawindowp.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSDnaWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDnaWindowENDCLASS = QtMocHelpers::stringData(
    "DnaWindow",
    "on_actionImportPatientData_triggered",
    "",
    "on_importViralDataButtonp_clicked",
    "on_actionExportResults_triggered",
    "on_actionQuit_triggered",
    "onAgeChanged",
    "age",
    "onGenderChanged",
    "index",
    "exportAnalysisToPdfp",
    "on_runSimulationButtonp_clicked",
    "on_clearDataButton_clicked",
    "on_analyzeResponseButtonp_clicked",
    "on_bloodTypeComboBox_currentIndexChanged",
    "on_virusTypeComboBox_currentIndexChanged",
    "on_parametersSlider_valueChanged",
    "value",
    "on_simulationDepthSpinBox_valueChanged",
    "on_importPatientDataButtonp_clicked",
    "on_virusParametersChanged",
    "updatePatientDataDisplay",
    "updateSimulationResults",
    "generateViralResponseChart",
    "generateImmuneResponseChart",
    "determineResponseType",
    "calculateBasicMetrics",
    "updateViralLoadChart",
    "QList<double>",
    "viralLoadData",
    "updateImmuneResponseChart",
    "immuneResponseData"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDnaWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  158,    2, 0x08,    1 /* Private */,
       3,    0,  159,    2, 0x08,    2 /* Private */,
       4,    0,  160,    2, 0x08,    3 /* Private */,
       5,    0,  161,    2, 0x08,    4 /* Private */,
       6,    1,  162,    2, 0x08,    5 /* Private */,
       8,    1,  165,    2, 0x08,    7 /* Private */,
      10,    0,  168,    2, 0x08,    9 /* Private */,
      11,    0,  169,    2, 0x08,   10 /* Private */,
      12,    0,  170,    2, 0x08,   11 /* Private */,
      13,    0,  171,    2, 0x08,   12 /* Private */,
      14,    1,  172,    2, 0x08,   13 /* Private */,
      15,    1,  175,    2, 0x08,   15 /* Private */,
      16,    1,  178,    2, 0x08,   17 /* Private */,
      18,    1,  181,    2, 0x08,   19 /* Private */,
      19,    0,  184,    2, 0x08,   21 /* Private */,
      20,    0,  185,    2, 0x08,   22 /* Private */,
      21,    0,  186,    2, 0x08,   23 /* Private */,
      22,    0,  187,    2, 0x08,   24 /* Private */,
      23,    0,  188,    2, 0x08,   25 /* Private */,
      24,    0,  189,    2, 0x08,   26 /* Private */,
      25,    0,  190,    2, 0x08,   27 /* Private */,
      26,    0,  191,    2, 0x08,   28 /* Private */,
      27,    1,  192,    2, 0x08,   29 /* Private */,
      30,    1,  195,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28,   31,

       0        // eod
};

Q_CONSTINIT const QMetaObject DnaWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSDnaWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDnaWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDnaWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DnaWindow, std::true_type>,
        // method 'on_actionImportPatientData_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_importViralDataButtonp_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionExportResults_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionQuit_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAgeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onGenderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'exportAnalysisToPdfp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_runSimulationButtonp_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clearDataButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_analyzeResponseButtonp_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bloodTypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_virusTypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_parametersSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_simulationDepthSpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_importPatientDataButtonp_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_virusParametersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePatientDataDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateSimulationResults'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateViralResponseChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateImmuneResponseChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'determineResponseType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'calculateBasicMetrics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateViralLoadChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<double> &, std::false_type>,
        // method 'updateImmuneResponseChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<double> &, std::false_type>
    >,
    nullptr
} };

void DnaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DnaWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionImportPatientData_triggered(); break;
        case 1: _t->on_importViralDataButtonp_clicked(); break;
        case 2: _t->on_actionExportResults_triggered(); break;
        case 3: _t->on_actionQuit_triggered(); break;
        case 4: _t->onAgeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onGenderChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->exportAnalysisToPdfp(); break;
        case 7: _t->on_runSimulationButtonp_clicked(); break;
        case 8: _t->on_clearDataButton_clicked(); break;
        case 9: _t->on_analyzeResponseButtonp_clicked(); break;
        case 10: _t->on_bloodTypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_virusTypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_parametersSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->on_simulationDepthSpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->on_importPatientDataButtonp_clicked(); break;
        case 15: _t->on_virusParametersChanged(); break;
        case 16: _t->updatePatientDataDisplay(); break;
        case 17: _t->updateSimulationResults(); break;
        case 18: _t->generateViralResponseChart(); break;
        case 19: _t->generateImmuneResponseChart(); break;
        case 20: _t->determineResponseType(); break;
        case 21: _t->calculateBasicMetrics(); break;
        case 22: _t->updateViralLoadChart((*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[1]))); break;
        case 23: _t->updateImmuneResponseChart((*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<double> >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *DnaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DnaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDnaWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DnaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_WARNING_POP
