TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11
SOURCES += \
    test.cpp


HEADERS +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/release/ -lfpSystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/debug/ -lfpSystem
else:unix: LIBS += -L$$PWD/../FlyPartEngine/Build/fpSystem/ -lfpSystem

INCLUDEPATH += $$PWD/../FlyPartEngine/Build/fpSystem
DEPENDPATH += $$PWD/../FlyPartEngine/Build/fpSystem

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/release/libfpSystem.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/debug/libfpSystem.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/release/fpSystem.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/debug/fpSystem.lib
else:unix: PRE_TARGETDEPS += $$PWD/../FlyPartEngine/Build/fpSystem/libfpSystem.a



unix|win32: LIBS += -lSDL2
