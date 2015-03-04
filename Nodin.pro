#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T07:23:21
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nodin
TEMPLATE = app

INCLUDEPATH += .

SOURCES += main.cpp\
    UI/NodeItem.cpp \
    UI/MainWindow.cpp \
    App/App.cpp \
    UI/ConnectionItem.cpp \
    App/Nodes/Node.cpp \
    App/Nodes/AdditionNode.cpp \
    App/Nodes/ConstantNode.cpp \
    App/Nodes/PrinterNode.cpp \
    App/Boundary/NodeProxy.cpp \
    App/Factories/NodeFactory.cpp \
    App/Factories/AdditionNodeFactoryDelegate.cpp \
    App/Factories/ConstantNodeFactoryDelegate.cpp \
    App/Factories/PrinterNodeFactoryDelegate.cpp \
    UI/NetworkSceneView.cpp

HEADERS  += \
    UI/NodeItem.h \
    UI/MainWindow.h \
    App/App.h \
    UI/ConnectionItem.h \
    App/Nodes/Node.h \
    App/Nodes/AdditionNode.h \
    App/Nodes/ConstantNode.h \
    App/Nodes/PrinterNode.h \
    App/Boundary/NodeProxy.h \
    App/Boundary/ConnectionProxy.h \
    App/Factories/NodeFactory.h \
    App/Factories/ConstantNodeFactoryDelegate.h \
    App/Factories/AdditionNodeFactoryDelegate.h \
    App/Factories/PrinterNodeFactoryDelegate.h \
    App/Factories/NodeFactoryDelegate.h \
    UI/NetworkSceneView.h