TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11
SOURCES += \
    test.cpp


HEADERS +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/release/ -lFlyPartEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/debug/ -lFlyPartEngine
else:unix: LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/ -lfpSystem

INCLUDEPATH += $$PWD/../FlyPartEngine/Build/FlyPartEngine
DEPENDPATH += $$PWD/../FlyPartEngine/Build/FlyPartEngine

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/FlyPartEngine/release/libfpSystem.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/debug/libFlyPartEngine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/release/FlyPartEngine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/debug/FlyPartEngine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/libFlyPartEngine.a



unix|win32: LIBS += -lSDL2
