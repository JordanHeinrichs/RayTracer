TEMPLATE = app
CONFIG += c++11 c++14 console release

INCLUDEPATH += .
win32: QMAKE_CXXFLAGS += /WX /O2 /MP4
!win32: QMAKE_CXXFLAGS += -Werror -O3 -Wno-ignored-qualifiers

# Input
HEADERS += *.h
SOURCES += *.cpp

DESTDIR = ../build
TARGET = assignment4

settings.path = ../build
settings.files = sceneSpecificationRc*
models.path = ../build
models.files = ../models/*
INSTALLS += settings models

OBJECTS_DIR = ../.tmp/.obj
MOC_DIR = ../.tmp/.moc
RCC_DIR = ../.tmp/.rcc
UI_DIR = ../.tmp/.ui
