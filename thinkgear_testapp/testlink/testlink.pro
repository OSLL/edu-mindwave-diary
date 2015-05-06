#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T02:25:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testlink
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ../thinkgear_testapp.cpp

HEADERS  += widget.h \
    ../thinkgear.h

FORMS    += widget.ui

LIBS += c:/ws/edu-mindwave-diary/thinkgear_testapp/thinkgear.lib
