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





#unix|win32: LIBS += -lSDL2

unix:!macx|win32: LIBS += -L$$PWD/../Build/fpSystem/ -lfpSystem

INCLUDEPATH += $$PWD/../Build/fpSystem
DEPENDPATH += $$PWD/../Build/fpSystem


