#-------------------------------------------------
#
# Project created by QtCreator 2020-08-02T19:06:53
#
#-------------------------------------------------

QT       += core gui  network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = program2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socket.cpp

HEADERS  += mainwindow.h \
    socket.h

FORMS    += mainwindow.ui
