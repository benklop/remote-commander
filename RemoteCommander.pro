#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T22:39:31
#
#-------------------------------------------------
CONFIG += serialport

QT       += core \
            network \
            serialport

QT       -= gui

TARGET = RemoteCommander
CONFIG   += console \
            c++11

CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11 \
                  -Wno-psabi

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

OTHER_FILES += \
    configfile.conf \
    README.md

target.path = .
INSTALLS += target
