QT += widgets

TARGET = sbs

INCLUDEPATH += $$PWD/src/commands \
    $$PWD/src/ui

SOURCES += src/main.cpp \
    src/ui/window.cpp \
    src/ui/cmd_dialog.cpp \
    src/commands/cmd_manager.cpp \
    src/commands/cmd_type.cpp

HEADERS  += \
    src/ui/window.h \
    src/ui/cmd_dialog.h \
    src/commands/cmd_manager.h \
    src/commands/cmd_type.h \
    src/commands/cmd.h \
    src/commands/cmd_result.h

FORMS    +=

RESOURCES += \
    systray.qrc
