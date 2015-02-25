#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T07:23:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CipherQt
TEMPLATE = app

INCLUDEPATH += .

SOURCES += main.cpp\
    UI/NodeItem.cpp \
    UI/MainWindow.cpp \
    App/Node.cpp \
    App/App.cpp \
    UI/ConnectionItem.cpp

HEADERS  += \
    UI/NodeItem.h \
    UI/MainWindow.h \
    App/Node.h \
    App/App.h \
    UI/ConnectionItem.h
