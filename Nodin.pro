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
INCLUDEPATH += ./External/lua-5.2.3/include
INCLUDEPATH += ./External/LuaBridge

LIBS += -L/Users/jefaramvangorp/Developer/C++/Nodin/Nodin/External/lua-5.2.3 -llua52

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
    UI/NetworkSceneView.cpp \
    App/Logger.cpp \
    App/Nodes/TextFileNode.cpp \
    App/Factories/TextFileNFDelegate.cpp \
    App/Factories/ConstantNFDelegate.cpp \
    App/Factories/AdditionNFDelegate.cpp \
    App/Factories/PrinterNFDelegate.cpp \
    App/BuiltInConnectorTypes.cpp \
    App/Lua/Lua.cpp \
    App/Lua/LuaNodeScript.cpp

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
    App/Factories/NodeFactoryDelegate.h \
    UI/NetworkSceneView.h \
    App/Logger.h \
    App/Nodes/TextFileNode.h \
    App/Factories/TextFileNFDelegate.h \
    App/Factories/AdditionNFDelegate.h \
    App/Factories/ConstantNFDelegate.h \
    App/Factories/PrinterNFDelegate.h \
    App/BuiltInConnectorTypes.h \
    App/Lua/Lua.h \
    App/Lua/LuaNodeScript.h

OTHER_FILES += ./Scripts/Lua/node.lua
