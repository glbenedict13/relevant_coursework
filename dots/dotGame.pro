#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T12:21:06
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dotGame
TEMPLATE = app


SOURCES += main.cpp\
        startscreen.cpp \
    gameboard.cpp \
    node.cpp \
    player.cpp \
    box.cpp

HEADERS  += startscreen.h \
    gameboard.h \
    node.h \
    player.h \
    box.h

FORMS    += startscreen.ui \
    gameboard.ui \
    box.ui
