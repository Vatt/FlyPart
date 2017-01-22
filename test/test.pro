TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11
SOURCES += \
    test.cpp


HEADERS +=







win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/release/FlyPartRuntime/ -lFlyPartRuntime
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/debug/FlyPartRuntime/ -lFlyPartRuntime
else:unix: CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/Debug/FlyPartRuntime/ -lFlyPartRuntime
else:unix: CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/Release/FlyPartRuntime/ -lFlyPartRuntime
INCLUDEPATH += $$PWD/../Build/Debug
DEPENDPATH += $$PWD/../Build/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/release/FlyPartRuntime/libFlyPartRuntime.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/debug/FlyPartRuntime/libFlyPartRuntime.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/release/FlyPartRuntime/FlyPartRuntime.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/debug/FlyPartRuntime/FlyPartRuntime.lib
else:unix: CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Build/Debug/FlyPartRuntime/libFlyPartRuntime.a
else:unix: CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Build/Release/FlyPartRuntime/libFlyPartRuntime.a
