#-------------------------------------------------
#
# Project created by QtCreator 2015-04-06T18:24:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sample3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
#  thinkgear.cpp

HEADERS  += mainwindow.h \
    thinkgear.h

FORMS    += mainwindow.ui

#INCLUDEPATH += "thinkgear.lib" \
#                "thinkgear.dll"

#LIBS += -lthinkgear
win32:LIBS += thinkgear.lib
