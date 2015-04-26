#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T22:55:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetoCAL
TEMPLATE = app
CONFIG += c++11
DESTDIR = $$PWD

SOURCES += main.cpp\
        mainwindow.cpp \
    graphviewer.cpp \
    connection.cpp \
    symbolics.cpp \
    preprocessing.cpp \
    parseLinhasMetro.cpp \
    parseLinhasAutocarro.cpp \
    optionsdialog.cpp \
    updatelines.cpp \
    outputcalcs.cpp

HEADERS  += mainwindow.h \
    graphviewer.h \
    Graph.h \
    edgetype.h \
    connection.h \
    symbolics.h \
    preprocessing.h \
    parseLinhasMetro.h \
    parseLinhasAutocarro.h \
    Local.h \
    LoadFile.h \
    optionsdialog.h \
    init.h \
    updatelines.h \
    outputcalcs.h

FORMS    += mainwindow.ui \
    optionsdialog.ui \
    updatelines.ui \
    outputcalcs.ui

DISTFILES += \
    GraphViewerController.jar
