#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T17:27:55
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HangMe
TEMPLATE = app


SOURCES += main.cpp\
        hangme.cpp \
    about.cpp \
    chat.cpp \
    client.cpp \
    connectionsetup.cpp \
    dictionary.cpp \
    endofgame.cpp \
    gamecontroller.cpp \
    gameview.cpp \
    highscore.cpp \
    server.cpp

HEADERS  += hangme.h \
    about.h \
    chat.h \
    client.h \
    connectionsetup.h \
    dictionary.h \
    endofgame.h \
    gamecontroller.h \
    gameview.h \
    highscore.h \
    server.h

FORMS    += hangme.ui \
    about.ui \
    chat.ui \
    connectionsetup.ui \
    dictionary.ui \
    endofgame.ui \
    gameview.ui \
    highscore.ui

RESOURCES += \
    resources.qrc
