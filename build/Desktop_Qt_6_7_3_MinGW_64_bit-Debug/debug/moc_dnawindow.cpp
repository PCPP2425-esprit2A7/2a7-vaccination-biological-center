/****************************************************************************
** Meta object code from reading C++ file 'dnawindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dnawindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dnawindow.h' doesn't include <QObject>."
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
    "on_importViralDataButton_clicked",
    "on_actionExportResults_triggered",
    "on_actionQuit_triggered",
    "on_exportResultsButton_clicked",
    "on_runSimulationButton_clicked",
    "on_clearDataButton_clicked",
    "on_analyzeResponseButton_clicked",
    "on_bloodTypeComboBox_currentIndexChanged",
    "index",
    "on_virusTypeComboBox_currentIndexChanged",
    "onAgeChanged",
    "age",
    "onGenderChanged",
    "gender",
    "on_parametersSlider_valueChanged",
    "value",
    "on_simulationDepthSpinBox_valueChanged",
    "on_importPatientDataButton_clicked",
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
    "QList<SimulationResult>",
    "results"
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
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x08,    1 /* Private */,
       3,    0,  153,    2, 0x08,    2 /* Private */,
       4,    0,  154,    2, 0x08,    3 /* Private */,
       5,    0,  155,    2, 0x08,    4 /* Private */,
       6,    0,  156,    2, 0x08,    5 /* Private */,
       7,    0,  157,    2, 0x08,    6 /* Private */,
       8,    0,  158,    2, 0x08,    7 /* Private */,
       9,    0,  159,    2, 0x08,    8 /* Private */,
      10,    1,  160,    2, 0x08,    9 /* Private */,
      12,    1,  163,    2, 0x08,   11 /* Private */,
      13,    1,  166,    2, 0x08,   13 /* Private */,
      15,    1,  169,    2, 0x08,   15 /* Private */,
      17,    1,  172,    2, 0x08,   17 /* Private */,
      19,    1,  175,    2, 0x08,   19 /* Private */,
      20,    0,  178,    2, 0x08,   21 /* Private */,
      21,    0,  179,    2, 0x08,   22 /* Private */,
      22,    0,  180,    2, 0x08,   23 /* Private */,
      23,    0,  181,    2, 0x08,   24 /* Private */,
      24,    0,  182,    2, 0x08,   25 /* Private */,
      25,    0,  183,    2, 0x08,   26 /* Private */,
      26,    0,  184,    2, 0x08,   27 /* Private */,
      27,    1,  185,    2, 0x08,   28 /* Private */,
      30,    1,  188,    2, 0x08,   30 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 31,   32,

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
        // method 'on_importViralDataButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionExportResults_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionQuit_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exportResultsButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_runSimulationButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clearDataButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_analyzeResponseButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bloodTypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_virusTypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onAgeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onGenderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_parametersSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_simulationDepthSpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_importPatientDataButton_clicked'
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
        QtPrivate::TypeAndForceComplete<const QVector<SimulationResult> &, std::false_type>
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
        case 1: _t->on_importViralDataButton_clicked(); break;
        case 2: _t->on_actionExportResults_triggered(); break;
        case 3: _t->on_actionQuit_triggered(); break;
        case 4: _t->on_exportResultsButton_clicked(); break;
        case 5: _t->on_runSimulationButton_clicked(); break;
        case 6: _t->on_clearDataButton_clicked(); break;
        case 7: _t->on_analyzeResponseButton_clicked(); break;
        case 8: _t->on_bloodTypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_virusTypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onAgeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->onGenderChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->on_parametersSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->on_simulationDepthSpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->on_importPatientDataButton_clicked(); break;
        case 15: _t->updatePatientDataDisplay(); break;
        case 16: _t->updateSimulationResults(); break;
        case 17: _t->generateViralResponseChart(); break;
        case 18: _t->generateImmuneResponseChart(); break;
        case 19: _t->determineResponseType(); break;
        case 20: _t->calculateBasicMetrics(); break;
        case 21: _t->updateViralLoadChart((*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[1]))); break;
        case 22: _t->updateImmuneResponseChart((*reinterpret_cast< std::add_pointer_t<QList<SimulationResult>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 21:
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
