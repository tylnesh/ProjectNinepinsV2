``````````#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T08:32:00
#
#-------------------------------------------------

QT       += core gui widgets serialport concurrent

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Ninepins_rpi_1.2.0
TEMPLATE = app

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    chooserwindow.cpp \
    fullgamewindow.cpp \
    global.cpp \
    partialgamewindow.cpp \
    gpioclass.cpp \
    changerwindow.cpp \
    delay.cpp \
    buttonchecker.cpp \
    isgreen.cpp \
    gaffe.cpp

HEADERS  += mainwindow.h \
    chooserwindow.h \
    fullgamewindow.h \
    global.h \
    partialgamewindow.h \
    gpioclass.h \
    changerwindow.h \
    delay.h \
    buttonchecker.h \
    isgreen.h \
    gaffe.h

FORMS    += mainwindow.ui \
    chooserwindow.ui \
    fullgamewindow.ui \
    partialgamewindow.ui \
    changerwindow.ui \
    delay.ui \
    isgreen.ui \
    gaffe.ui


RESOURCES += \
    ninepins.qrc
