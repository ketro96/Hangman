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
    game.cpp \
    dictionary.cpp \
    highscore.cpp


HEADERS  += hangman.h \
    connectionsetup.h \
    server.h \
    client.h \
    chat.h \
    game.h \
    dictionary.h \
    highscore.h

FORMS    += hangman.ui \
    connectionsetup.ui \
    chat.ui \
    game.ui \
    dictionary.ui \
    highscore.ui
