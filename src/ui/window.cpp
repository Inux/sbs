#include "window.h"

#include "cmd_dialog.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QDate>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <qfileinfo.h>

Window::Window()
{
    createCommands();
    createCmdSelectGroupBox();
    createCmdGroupBox();

    createActions();
    createTrayIcon();

    connect(executeCommandButton, &QAbstractButton::clicked, this, &Window::executeCommand);
    connect(cmdNewButton, &QAbstractButton::clicked, this, &Window::showCmdDialog);
    connect(cmdDeleteButton, &QAbstractButton::clicked, this, &Window::showMessage);
    connect(cmdSelectComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Window::setCmdOfEditor);
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &Window::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::iconActivated);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(cmdSelectGroupBox);
    mainLayout->addWidget(cmdGroupBox);
    setLayout(mainLayout);

    cmdSelectComboBox->setCurrentIndex(1);
    trayIcon->show();

    setWindowTitle(tr("Systray"));
    resize(400, 300);
}

void Window::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray Scripts"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void Window::setCmdOfEditor(int index)
{
    qDebug() << "Index: " << index;
    QIcon icon = cmdSelectComboBox->itemIcon(index);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    auto cmdPair = cmdManager->getCmdByIndex(index);
    cmdTypeEdit->setText(Commands::getTypeString(cmdPair.second.cmdType));
    cmdNameEdit->setText(cmdPair.second.name);
    cmdScriptEdit->setText(cmdPair.second.scriptPath);

    trayIcon->setToolTip(cmdSelectComboBox->itemText(index));
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        cmdSelectComboBox->setCurrentIndex((cmdSelectComboBox->currentIndex() + 1) % cmdSelectComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void Window::showMessage()
{

}

void Window::showCmdDialog()
{
    CmdDialog* cmdDialog = new CmdDialog();
    cmdDialog->show();
}

void Window::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void Window::executeCommand()
{
    QString key = cmdSelectComboBox->itemText(cmdSelectComboBox->currentIndex());
    qDebug() << key;
    auto pos = cmdManager->getCmds().find(key);
    if(pos != cmdManager->getCmds().end()) {
        Commands::Cmd cmd = pos->second;
        qDebug() << "Executing: " << cmd.name;
        Commands::CmdResult res = cmdManager->execute(cmd.name);

        if(res.result) {
            trayIcon->setIcon(QIcon(":/images/heart.png"));
            trayIcon->showMessage(cmd.name,
                                  cmd.scriptPath + " executed Successfully!",
                                  QSystemTrayIcon::Critical,
                                  5000);
        } else {
            QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::Warning;
            trayIcon->setIcon(QIcon(":/images/heart.png"));
            trayIcon->showMessage(cmd.name,
                                  cmd.scriptPath + " execution Problem!\n" +
                                  "Output: \n" + res.errors,
                                  msgIcon,
                                  5000);
        }
    }
}

void Window::createCmdSelectGroupBox()
{
    cmdSelectGroupBox = new QGroupBox(tr("Commands"));

    cmdSelectLabel = new QLabel("Command:");

    cmdSelectComboBox = new QComboBox;
    qDebug() << "Add Command to UI:";
    qDebug() << "commands size: " << cmdManager->getCmds().size();
    for(auto& c : cmdManager->getCmds()) {
        qDebug() << c.first;
        qDebug() << "Script: " << c.second.name;
        cmdSelectComboBox->addItem(QIcon(":/images/heart.png"),
                              c.second.name);
    }

    executeCommandButton = new QPushButton(tr("Execute Command"));
    executeCommandButton->setDefault(true);

    //Details of Command

    cmdTypeLabel = new QLabel(tr("Type:"));
    cmdTypeEdit = new QLineEdit(tr("Command Type"));
    cmdTypeEdit->setReadOnly(true);

    cmdNameLabel = new QLabel(tr("Name:"));
    cmdNameEdit = new QLineEdit(tr("Command"));
    cmdNameEdit->setReadOnly(true);

    cmdScriptLabel = new QLabel(tr("Script Path:"));
    cmdScriptEdit = new QLineEdit(tr("/path/to/script.sh"));
    cmdScriptEdit->setReadOnly(true);

    cmdNewLabel = new QLabel(tr("New:"));
    cmdNewButton = new QPushButton(tr("New"));
    cmdNewButton->setDefault(true);

    cmdDeleteButton = new QPushButton(tr("Delete"));
    QPalette palette = cmdDeleteButton->palette();
    palette.setColor(QPalette::ButtonText, QColor(Qt::red));
    cmdDeleteButton->setPalette(palette);
    cmdDeleteButton->update();

    QGridLayout* cmdLayout = new QGridLayout;
    cmdLayout->addWidget(cmdSelectLabel, 0, 0, 1, 1);
    cmdLayout->addWidget(cmdSelectComboBox, 0, 1, 1, 3);
    cmdLayout->addWidget(executeCommandButton, 0, 4, 1, 2);
    cmdLayout->addWidget(cmdTypeLabel, 1, 0, 1, 1);
    cmdLayout->addWidget(cmdTypeEdit, 1, 1, 1, 5);
    cmdLayout->addWidget(cmdNameLabel, 2, 0, 1, 1);
    cmdLayout->addWidget(cmdNameEdit, 2, 1, 1, 5);
    cmdLayout->addWidget(cmdScriptLabel, 3, 0, 1, 1);
    cmdLayout->addWidget(cmdScriptEdit, 3, 1, 1, 5);
    cmdLayout->addWidget(cmdDeleteButton, 4, 5, 1, 1);
    cmdSelectGroupBox->setLayout(cmdLayout);
}

void Window::createCmdGroupBox() {
    cmdGroupBox = new QGroupBox(tr("Editor"));

    cmdNewLabel = new QLabel(tr("New:"));
    cmdNewButton = new QPushButton(tr("New"));
    cmdNewButton->setDefault(true);

    QGridLayout *cmdLayout = new QGridLayout;
    cmdLayout->addWidget(cmdNewLabel, 0, 0);
    cmdLayout->addWidget(cmdNewButton, 0, 1, 1, 1);
    cmdLayout->setColumnStretch(2, 1);
    cmdLayout->setRowStretch(1, 1);
    cmdGroupBox->setLayout(cmdLayout);
}

void Window::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void Window::createCommands()
{
    cmdManager = new Commands::CmdManager();
    cmdManager->loadSettings();

    /*Commands::Cmd cmdOne = {Commands::PYTHON,
            "Python Hello World",
            ":/scripts/test/hello_world.py"};

    Commands::Cmd cmdTwo = {Commands::BASH,
            "Bash Hello World",
            ":/scripts/test/hello_world.sh"};

    cmdManager->add(cmdOne);
    cmdManager->add(cmdTwo);
    */

    qDebug() << "Added following commands:";
    for(auto& c : cmdManager->getCmds()) {
        qDebug() << c.first;
        qDebug() << "Script: " << c.second.scriptPath;
    }

    cmdManager->saveSettings();
}

#endif
