#-------------------------------------------------
#
# Project created by QtCreator 2020-05-12T03:04:10
#
#-------------------------------------------------

QT       += core gui network sql xml
QT += serialport
QT +=printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = serialport
TARGET = mainwindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_port.cpp \
    qcustomplot.cpp \
    socketclient.cpp

HEADERS  += mainwindow.h \
    my_port.h \
    qcustomplot.h \
    socketclient.h \
    base_pragram.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
