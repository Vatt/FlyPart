TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11
SOURCES += \
    test.cpp


HEADERS +=



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/x64/release/ -lFlyPartEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/x64/debug/ -lFlyPartEngine
else:unix: LIBS += -L$$PWD/../Build/x64/ -lFlyPartEngine

INCLUDEPATH += $$PWD/../Build/x64/Debug
DEPENDPATH += $$PWD/../Build/x64/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/x64/release/libFlyPartEngine.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/x64/debug/libFlyPartEngine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/x64/release/FlyPartEngine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/x64/debug/FlyPartEngine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../Build/x64/libFlyPartEngine.a
