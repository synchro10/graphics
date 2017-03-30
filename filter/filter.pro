#-------------------------------------------------
#
# Project created by QtCreator 2017-03-26T20:52:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filter
TEMPLATE = app


SOURCES += main.cpp\
        view.cpp \
    executor.cpp \
    model.cpp \
    drawingarea.cpp \
    zone.cpp \
    controlpanel.cpp \
    zonea.cpp \
    zoneb.cpp \
    filter.cpp \
    blackwhitefilter.cpp \
    negativefilter.cpp

HEADERS  += view.h \
    executor.h \
    model.h \
    drawingarea.h \
    zone.h \
    controlpanel.h \
    zonea.h \
    zoneb.h \
    filter.h \
    blackwhitefilter.h \
    negativefilter.h
