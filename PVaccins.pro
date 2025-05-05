# Configuration de base
TEMPLATE = app
TARGET = PVaccins

# Configuration du compilateur
CONFIG += c++17
CONFIG -= debug_and_release debug_and_release_target

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += $$PWD/qrcodegen
SOURCES += $$PWD/qrcodegen/QrCode.cpp
# Force debug build pour avoir plus d'informations
CONFIG += debug

# Modules Qt nécessaires
QT += core gui sql multimedia multimediawidgets widgets charts serialport network pdf printsupport svg



# Fichiers sources
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    crud.cpp \
    connection.cpp \
    serialhandler.cpp \
    smtp_mailer_secure.cpp \
    AIAssistantWindow.cpp \
    diseasespreadmodel.cpp \
    openaichatbot.cpp \
    simulationdialog.cpp \
    arduino.cpp\
    dnaanalyzerp.cpp \
    dnawindowp.cpp \
    patientdatap.cpp \
    patientdetailsdialogp.cpp \
    simulationenginep.cpp \
    viraldatap.cpp \
    animatedbaritemp.cpp \
    viralresponsep.cpp \
    conccurance.cpp \
    mainwindow_copier.cpp \
    predictionmodel.cpp \
    predictivemaintenancedialog.cpp


HEADERS += \
    AnimatedBarItem.h \
    mainwindow.h \
    crud.h \
    connection.h \
    serialhandler.h \
    smtp_mailer_secure.h \
    AIAssistantWindow.h \
    diseasespreadmodel.h \
    openaichatbot.h \
    simulationdialog.h \
    arduino.h \
    dnaanalyzerp.h \
    dnawindowp.h \
    patientdatap.h \
    patientdetailsdialogp.h \
    simulationenginep.h \
    viraldatap.h \
    animatedbaritemp.h \
    viralresponsep.h  \
    conccurance.h  \
    clickablelabel.h \
    mainwindow_copier.h \
    predictionmodel.h \
    predictivemaintenancedialog.h

FORMS += \
    AIAssistantWindow.ui \
    mainwindow.ui \
    simulationdialog.ui \
    dnawindowp.ui \
    patientdetailsdialogp.ui \
    predictivemaintenancedialog.ui

# Ressources
RESOURCES += \
    image1.qrc \
    image2.qrc \
    IMAGE.qrc \
    res.qrc \
    ressource.qrc \
    waaa.qrc

# Dossiers de sortie
DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/obj
MOC_DIR = $$PWD/build/moc
RCC_DIR = $$PWD/build/rcc
UI_DIR = $$PWD/build/ui

# Nettoyage supplémentaire
QMAKE_CLEAN += \
    $$DESTDIR/*.exe \
    $$DESTDIR/*.dll \
    $$OBJECTS_DIR/*.o \
    $$MOC_DIR/moc_*.cpp \
    $$RCC_DIR/qrc_*.cpp \
    $$UI_DIR/ui_*.h

# Déploiement
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Messages de débogage
message("Qt version: $$QT_VERSION")
message("Qt modules: $$QT")
message("Compiler: $$QMAKE_CXX")
message("Build mode: $$CONFIG")
