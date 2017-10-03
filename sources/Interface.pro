#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T15:49:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controllermainwindow.cpp \
    modelmainwindow.cpp \
    myscene.cpp \
    modelmap.cpp

HEADERS  += mainwindow.h \
    controllermainwindow.h \
    modelmainwindow.h \
    myscene.h \
    modelmap.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images/images.qrc
