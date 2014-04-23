TEMPLATE = lib
CONFIG += staticlib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = $$qtLibraryTarget(FlyPart)
QMAKE_CXXFLAGS += -std=c++11
HEADERS += \
    util/fpCallback.h \
    util/fpFunction.h \
    sys/fpInputSystem.h \
    sys/fpKeyboard.h \
    sys/fpSystemInterface.h \
    sys/fpWindow.h \
    sys/fpWindowSystem.h \
    sys/sdl/fpKeyboardSDL.h \
    sys/sdl/fpWindowSDL_GL.h \
    sys/fpKeybind.h \
    include/gl/glcorearb.h \
    sys/impl/SDL/fpKeyboardSDL.h \
    sys/impl/SDL/fpWindowSDL_GL.h \
    sys/input/fpKeybind.h \
    sys/input/fpKeyboard.h \
    FlyPart.h \
    sys/input/fpKey.h

SOURCES += \
    sys/fpInputSystem.cpp \
    sys/fpWindow.cpp \
    sys/fpWindowSystem.cpp \
    sys/impl/SDL/fpKeyboardSDL.cpp \
    sys/impl/SDL/fpWindowSDL_GL.cpp \
    sys/input/fpKeybind.cpp



