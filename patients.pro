QT       += core gui sql printsupport charts
QT += core gui widgets sql
QT += pdf
QT += core gui charts widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Crud.cpp \
    animatedbaritem.cpp \
    connection.cpp \
    dnaanalyzer.cpp \
    dnawindow.cpp \
    main.cpp \
    mainwindow.cpp \
    patientdata.cpp \
    patientdetailsdialog.cpp \
    simulationengine.cpp \
    viraldata.cpp \
    viralresponse.cpp

HEADERS += \
    Crud.h \
    animatedbaritem.h \
    connection.h \
    dnaanalyzer.h \
    dnawindow.h \
    mainwindow.h \
    patientdata.h \
    patientdetailsdialog.h \
    simulationengine.h \
    viraldata.h \
    viralresponse.h

FORMS += \
    dnawindow.ui \
    mainwindow.ui \
    patientdetailsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Patient.qrc
