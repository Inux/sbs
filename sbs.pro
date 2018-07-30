QT      += widgets

TARGET = sbs

INCLUDEPATH += $$PWD/src/commands \
    $$PWD/src/ui

SOURCES += src/main.cpp \
    src/ui/window.cpp \
    src/commands/cmds.cpp \
    src/commands/cmd.cpp

HEADERS  += \
    src/ui/window.h \
    src/commands/cmds.h \
    src/commands/cmd.h \
    src/commands/cmdtype.h

FORMS    +=

RESOURCES += \
    systray.qrc
