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
INCLUDEPATH += ./External/Selene/include

LIBS += -L/Users/jefaramvangorp/Developer/C++/Nodin/Nodin/External/lua-5.2.3 -llua52

SOURCES += main.cpp\
    UI/NodeItem.cpp \
    UI/MainWindow.cpp \
    App/App.cpp \
    UI/ConnectionItem.cpp \
    App/Nodes/Node.cpp \
    App/Nodes/ConstantNode.cpp \
    App/Boundary/NodeProxy.cpp \
    App/Factories/NodeFactory.cpp \
    UI/NetworkSceneView.cpp \
    App/Logger.cpp \
    App/Factories/ConstantNFDelegate.cpp \
    App/BuiltInConnectorTypes.cpp \
    App/Lua/LuaNodeScript.cpp \
    UI/TypesWidget.cpp \
    App/Nodes/LuaNode.cpp \
    App/Factories/LuaNFDelegate.cpp \
    System/QtBasedFileSystem.cpp \
    UI/ScriptEditorWindow.cpp \
    UI/CreateConstantDialog.cpp

HEADERS  += \
    UI/NodeItem.h \
    UI/MainWindow.h \
    App/App.h \
    UI/ConnectionItem.h \
    App/Nodes/Node.h \
    App/Nodes/ConstantNode.h \
    App/Boundary/NodeProxy.h \
    App/Boundary/ConnectionProxy.h \
    App/Factories/NodeFactory.h \
    App/Factories/NodeFactoryDelegate.h \
    UI/NetworkSceneView.h \
    App/Logger.h \
    App/Factories/ConstantNFDelegate.h \
    App/BuiltInConnectorTypes.h \
    App/Lua/LuaNodeScript.h \
    UI/TypesWidget.h \
    App/Nodes/LuaNode.h \
    App/Factories/LuaNFDelegate.h \
    App/FileSystem.h \
    System/QtBasedFileSystem.h \
    UI/ScriptEditorWindow.h \
    UI/CreateConstantDialog.h

OTHER_FILES += ./NodeScripts/Lua/add.lua
OTHER_FILES += ./NodeScripts/Lua/subtract.lua
OTHER_FILES += ./NodeScripts/Lua/logger.lua
OTHER_FILES += ./NodeScripts/Lua/read_text_file.lua
OTHER_FILES += ./NodeScripts/Lua/write_text_file.lua
