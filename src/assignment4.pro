TEMPLATE = app
CONFIG += c++11 debug console

INCLUDEPATH += .
win32: QMAKE_CXXFLAGS += /WX

# Input
HEADERS += *.h
SOURCES += *.cpp

DESTDIR = ../build
TARGET = assignment4

OBJECTS_DIR = ../.tmp/.obj
MOC_DIR = ../.tmp/.moc
RCC_DIR = ../.tmp/.rcc
UI_DIR = ../.tmp/.ui
