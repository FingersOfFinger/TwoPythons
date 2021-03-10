TEMPLATE-app

QT+=widgets
QT+=network
QT+=core gui

SOURCES += \
        Authorization.cpp \
        Lobby.cpp \
        Registration.cpp \
        gamewindow.cpp \
        main.cpp \
        python.cpp

HEADERS += \
    Authorization.h \
    Lobby.h \
    Registration.h \
    gamewindow.h \
    python.h

FORMS += \
    Lobby.ui
