#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T18:10:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = isolines
TEMPLATE = app


SOURCES += main.cpp\
        view.cpp \
    drawingarea.cpp \
    zone.cpp \
    legend.cpp

HEADERS  += view.h \
    drawingarea.h \
    zone.h \
    legend.h
