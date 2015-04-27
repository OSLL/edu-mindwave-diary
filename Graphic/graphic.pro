#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T16:31:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    values.cpp

HEADERS  += \
    mainwindow.h \
    qcustomplot.h \
    libraries.h \
    values.h

FORMS    += mainwindow.ui

QT       += core gui widgets printsupport
