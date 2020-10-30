#-------------------------------------------------
#
# Project created by QtCreator 2020-08-29T16:09:09
#
#-------------------------------------------------

QT       += core gui network xml
QT += serialport
QT +=printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = start_work
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socket.cpp \
    my_port.cpp

HEADERS  += mainwindow.h \
    socket.h \
    my_port.h \
    my_tables.h

FORMS    += mainwindow.ui

DISTFILES += \
    img/scan.png

RESOURCES += \
    source.qrc
