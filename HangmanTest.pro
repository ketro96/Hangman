#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T09:39:27
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HangmanTest
TEMPLATE = app


SOURCES += main.cpp\
        hangman.cpp \
    connectionsetup.cpp \
    server.cpp \
    client.cpp \
    chat.cpp \
    dictionary.cpp \
    highscore.cpp \
    gamecontroller.cpp \
    gameview.cpp


HEADERS  += hangman.h \
    connectionsetup.h \
    server.h \
    client.h \
    chat.h \
    dictionary.h \
    highscore.h \
    gamecontroller.h \
    gameview.h

FORMS    += hangman.ui \
    connectionsetup.ui \
    chat.ui \
    dictionary.ui \
    highscore.ui \
    gameview.ui
