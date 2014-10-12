#-------------------------------------------------
#
# Project created by QtCreator 2014-10-11T10:13:05
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = weather
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    weather.cpp \
    sender.cpp \
    dataanalyze.cpp

HEADERS += \
    weather.h \
    sender.h \
    dataanalyze.h

RESOURCES += \
    weather.qrc
