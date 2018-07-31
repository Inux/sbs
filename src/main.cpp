#include <QApplication>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDebug>
#include <QMessageBox>
#include <QVariant>
#include <qmetatype.h>
#include "ui/window.h"

QDataStream& operator<<(QDataStream& out, const Commands::Cmd& v) {
    out << v.cmdType << v.name << v.scriptPath;
    qDebug() << v.cmdType << v.name << v.scriptPath;
    return out;
}

QDataStream& operator>>(QDataStream& in, Commands::Cmd& v) {
    int i;
    in >> i;
    v.cmdType = static_cast<Commands::CmdType>(i);
    in >> v.name;
    in >> v.scriptPath;
    qDebug() << v.cmdType << v.name << v.scriptPath;
    return in;
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);
    qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");
    qRegisterMetaTypeStreamOperators<Commands::Cmd>("Commands::Cmd");

    QCoreApplication::setOrganizationName("inux");
    QCoreApplication::setOrganizationDomain("steveineichen.ch");
    QCoreApplication::setApplicationName("sbs");
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray Scripts"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
    window.show();
    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif
