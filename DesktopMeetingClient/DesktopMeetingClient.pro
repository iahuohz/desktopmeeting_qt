#-------------------------------------------------
#
# Project created by QtCreator 2012-08-17T14:39:18
#
#-------------------------------------------------

QT       += core gui
CONFIG += thread

TARGET = DesktopMeetingClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    setdialog.cpp \
    recvthread.cpp

HEADERS  += mainwindow.h \
    common.h \
    setdialog.h \
    recvthread.h

FORMS    += mainwindow.ui \
    setdialog.ui
