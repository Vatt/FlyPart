TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11
SOURCES += \
    test.cpp


HEADERS +=






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/release/ -lFlyPartEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/debug/ -lFlyPartEngine
else:unix: LIBS += -L$$PWD/../Build/ -lFlyPartEngine

INCLUDEPATH += $$PWD/../Build/Debug
DEPENDPATH += $$PWD/../Build/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/release/libFlyPartEngine.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/debug/libFlyPartEngine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/release/FlyPartEngine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/debug/FlyPartEngine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../Build/libFlyPartEngine.a
