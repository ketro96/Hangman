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
    clientserver.cpp \
    connectionsetup.cpp \
    game.cpp \
    server.cpp

HEADERS  += hangman.h \
    clientserver.h \
    connectionsetup.h \
    game.h \
    server.h

FORMS    += hangman.ui \
    connectionsetup.ui \
    game.ui
