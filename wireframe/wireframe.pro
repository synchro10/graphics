#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T15:08:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wireframe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        view.cpp \
    drawingarea.cpp \
    viewmodel.cpp \
    model.cpp \
    optionsdialog.cpp \
    engine/graphicengine.cpp \
    engine/object.cpp \
    engine/camera.cpp \
    wire/wiremodel.cpp \
    engine/graphics2d.cpp \
    bspline/bspline.cpp \
    engine/parser.cpp

HEADERS  += view.h \
    drawingarea.h \
    viewmodel.h \
    model.h \
    optionsdialog.h \
    engine/graphicengine.h \
    engine/object.h \
    engine/camera.h \
    wire/wiremodel.h \
    engine/graphics2d.h \
    bspline/bspline.h \
    settings.h \
    engine/parser.h
