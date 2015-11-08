#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T09:44:46
#
#-------------------------------------------------

QT       += core gui

TARGET = DesktopMeetingServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    common.h

FORMS    += mainwindow.ui

LIBS += -lX11 -lXfixes
