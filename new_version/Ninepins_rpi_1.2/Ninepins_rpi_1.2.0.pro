#-------------------------------------------------
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
    global.cpp \
    gpioclass.cpp \
    changerwindow.cpp \
    delay.cpp \
    buttonchecker.cpp \
    gaffe.cpp \
    serialcomm.cpp \
    gamewindow.cpp

HEADERS  += mainwindow.h \
    chooserwindow.h \
    global.h \
    gpioclass.h \
    changerwindow.h \
    delay.h \
    buttonchecker.h \
    gaffe.h \
    serialcomm.h \
    gamewindow.h

FORMS    += mainwindow.ui \
    chooserwindow.ui \
    gamewindow.ui \
    changerwindow.ui \
    delay.ui \
    gaffe.ui \



RESOURCES += \
    ninepins.qrc

target.path = /home/pi
INSTALLS += target
