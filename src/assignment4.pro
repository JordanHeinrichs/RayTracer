TEMPLATE = app
CONFIG += c++11 release console

INCLUDEPATH += .
win32: QMAKE_CXXFLAGS += /WX /O2
!win32: QMAKE_CXXFLAGS += -Werror -O3

# Input
HEADERS += *.h
SOURCES += *.cpp

DESTDIR = ../build
TARGET = assignment4

settings.path = ../build
settings.files = sceneSpecificationRc
INSTALLS += settings

OBJECTS_DIR = ../.tmp/.obj
MOC_DIR = ../.tmp/.moc
RCC_DIR = ../.tmp/.rcc
UI_DIR = ../.tmp/.ui
