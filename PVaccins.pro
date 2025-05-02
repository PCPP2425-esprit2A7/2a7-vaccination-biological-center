# Configuration de base
TEMPLATE = app
TARGET = PVaccins

# Configuration du compilateur
CONFIG += c++17
CONFIG -= debug_and_release debug_and_release_target



QT += serialport
# Force debug build pour avoir plus d'informations
CONFIG += debug

# Modules Qt nécessaires
QT += core gui sql multimedia multimediawidgets widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# Fichiers sources
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    crud.cpp \
    connection.cpp \
    serialhandler.cpp \
    smtp_mailer_secure.cpp

HEADERS += \
    AnimatedBarItem.h \
    mainwindow.h \
    crud.h \
    connection.h \
    serialhandler.h \
    smtp_mailer_secure.h

FORMS += \
    mainwindow.ui

# Ressources
RESOURCES += \
    image1.qrc \
    image2.qrc

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
