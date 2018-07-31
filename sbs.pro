QT += widgets

TARGET = sbs

INCLUDEPATH += $$PWD/src/commands \
    $$PWD/src/ui

SOURCES += src/main.cpp \
    src/ui/window.cpp \
    src/commands/cmdmanager.cpp

HEADERS  += \
    src/ui/window.h \
    src/commands/cmdmanager.h \
    src/commands/cmdtype.h \
    src/commands/cmd.h \
    src/commands/cmdresult.h

FORMS    +=

RESOURCES += \
    systray.qrc
