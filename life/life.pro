#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T18:44:38
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life
TEMPLATE = app


SOURCES += main.cpp\
        view.cpp \
    field.cpp \
    model.cpp \
    controller.cpp

HEADERS  += view.h \
    field.h \
    model.h \
    controller.h
