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
    drawingarea.cpp \
    zone.cpp \
    controlpanel.cpp \
    zonea.cpp \
    zoneb.cpp \
    filter.cpp \
    blackwhitefilter.cpp \
    negativefilter.cpp \
    blurfilter.cpp \
    sharpenfilter.cpp \
    waterfilter.cpp \
    upscaledfilter.cpp \
    rotatewidget.cpp \
    rotatefilter.cpp \
    gammawidget.cpp \
    gammafilter.cpp \
    embossfilter.cpp \
    edgewidget.cpp \
    edgerobertfilter.cpp \
    edgesobelfilter.cpp

HEADERS  += view.h \
    executor.h \
    drawingarea.h \
    zone.h \
    controlpanel.h \
    zonea.h \
    zoneb.h \
    filter.h \
    blackwhitefilter.h \
    negativefilter.h \
    blurfilter.h \
    sharpenfilter.h \
    waterfilter.h \
    upscaledfilter.h \
    rotatewidget.h \
    rotatefilter.h \
    gammawidget.h \
    gammafilter.h \
    embossfilter.h \
    edgewidget.h \
    edgerobertfilter.h \
    edgesobelfilter.h
