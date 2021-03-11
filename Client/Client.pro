QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization.cpp \
    authorizationview.cpp \
    createlobby.cpp \
    gamewindow.cpp \
    lobby.cpp \
    main.cpp \
    mainwindow.cpp \
    python.cpp \
    registration.cpp \
    registrationview.cpp

HEADERS += \
    authorization.h \
    authorizationview.h \
    createlobby.h \
    gamewindow.h \
    lobby.h \
    mainwindow.h \
    python.h \
    registration.h \
    registrationview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    lobby.ui
