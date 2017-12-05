#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T11:40:56
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SystemMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sensoresthread.cpp \
    hwdcheck.cpp \
    usercheck.cpp \
    netcheck.cpp

HEADERS  += mainwindow.h \
    sensoresthread.h \
    hwdcheck.h \
    usercheck.h \
    netcheck.h

FORMS    += mainwindow.ui
