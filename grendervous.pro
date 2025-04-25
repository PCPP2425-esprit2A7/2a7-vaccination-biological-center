QT       += core gui sql printsupport widgets network

QT += svg

QT += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/qrcodegen
SOURCES += $$PWD/qrcodegen/QrCode.cpp \
    smtp_mailer_secure.cpp


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    main.cpp \
    grendervous.cpp \
    rendervous.cpp \

HEADERS += \
    connection.h \
    grendervous.h \
    rendervous.h \
    smtp_mailer_secure.h

FORMS += \
    grendervous.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
