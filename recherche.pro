QT       += core gui sql charts widgets network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AIAssistantWindow.cpp \
    Crud.cpp \
    connection.cpp \
    diseasespreadmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    openaichatbot.cpp \
    simulationdialog.cpp

HEADERS += \
    AIAssistantWindow.h \
    Crud.h \
    connection.h \
    diseasespreadmodel.h \
    mainwindow.h \
    openaichatbot.h \
    simulationdialog.h

FORMS += \
    AIAssistantWindow.ui \
    mainwindow.ui \
    simulationdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    IMAGE.qrc \
    ressource.qrc
