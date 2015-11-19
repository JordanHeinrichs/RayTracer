TEMPLATE = app
CONFIG += c++11 debug console

INCLUDEPATH += .

# Input
HEADERS += *.h
SOURCES += *.cpp

DESTDIR = ../build
TARGET = assignment4
shaders.path = ../build

OBJECTS_DIR = ../.tmp/.obj
MOC_DIR = ../.tmp/.moc
RCC_DIR = ../.tmp/.rcc
UI_DIR = ../.tmp/.ui
