#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T22:39:31
#
#-------------------------------------------------

QT       += core \
            network

QT       -= gui

TARGET = RemoteCommander
CONFIG   += console \
            serialport \
            c++11

CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += main.cpp \
    lircinterface.cpp \
    samsunginterface.cpp \
    commander.cpp \
    deviceinterface.cpp \
    mythtvinterface.cpp \
    networkinterface.cpp \
    magicPacket.cpp \
    macroaction.cpp

HEADERS += \
    lircinterface.h \
    samsunginterface.h \
    commander.h \
    deviceinterface.h \
    mythtvinterface.h \
    networkinterface.h \
    magicPacket.h \
    macroaction.h
