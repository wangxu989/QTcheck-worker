QT       += core gui network
QT += sql
QT +=xml
QT +=printsupport
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Qrcode
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



#LIBS += -L/usr/local/sqlite_arm/lib -lsqlite3
#INCLUDEPATH += /usr/local/sqlite_arm/include
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/qrencodeh/

DEFINES += HAVE_CONFIG_H

SOURCES += \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    process_bar.cpp \
    tab.cpp \
    socket.cpp \
    program2.cpp \
    qrencodecpp/bitstream.c \
    qrencodecpp/mask.c \
    qrencodecpp/mmask.c \
    qrencodecpp/mqrspec.c \
    qrencodecpp/qrinput.c \
    qrencodecpp/qrspec.c \
    qrencodecpp/rsecc.c \
    qrencodecpp/qrencode.c \
    qrencodecpp/split.c \
    start_finish_work.cpp \
    base_program.cpp \
    my_port.cpp \
    programwork.cpp \
    finish_work.cpp \
    my_tablewidget.cpp

HEADERS += \
    database.h \
    mainwindow.h \
    process_bar.h \
    tab.h \
    socket.h \
    base_program.h \
    program2.h \
    qrencodeh/bitstream.h \
    qrencodeh/config.h \
    qrencodeh/mask.h \
    qrencodeh/mmask.h \
    qrencodeh/mqrspec.h \
    qrencodeh/qrencode.h \
    qrencodeh/qrencode_inner.h \
    qrencodeh/qrinput.h \
    qrencodeh/qrspec.h \
    qrencodeh/rsecc.h \
    qrencodeh/split.h \
    start_finish_work.h \
    my_port.h \
    base_factory.h \
    programwork.h \
    qmessage_remind.h \
    keyboard.h \
    finish_work.h \
    my_tablewidget.h \
    myledit.h

FORMS += \
    form.ui \
    mainwindow.ui \
    program2.ui \
    start_finish_work.ui \
    programwork.ui \
    finish_work.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qrencodecpp/acinclude.m4 \
    qrencodecpp/aclocal.m4 \
    qrencodecpp/qrencode \
    qrencodeh/0.sh \
    qrencodeh/autogen.sh \
    qrencodecpp/configure.ac \
    qrencodecpp/libqrencode.pc \
    qrencodecpp/libqrencode.pc.in \
    qrencodecpp/qrencode.1 \
    qrencodecpp/qrencode.1.in \
    qrencodeh/config.h.in \
    qrencodeh/stamp-h1 \
    qrencodeh/ChangeLog \
    qrencodeh/0.sh \
    qrencodeh/autogen.sh \
    qrencodeh/config.h.in \
    qrencodeh/stamp-h1 \
    qrencodeh/ChangeLog

RESOURCES += \
    img.qrc
