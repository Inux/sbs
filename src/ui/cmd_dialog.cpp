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

CmdDialog::CmdDialog()
{
    createCmdGroupBox();
    
    createActions();
 
    connect(cmdSaveButton, &QAbstractButton::clicked, this, &CmdDialog::saveCommand);
    connect(cmdAbortButton, &QAbstractButton::clicked, this, &CmdDialog::abortCommand);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(cmdGroupBox);
    setLayout(mainLayout);

    setWindowTitle(tr("New Command"));
    resize(400, 300);
}

void CmdDialog::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void CmdDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void CmdDialog::saveCommand()
{
}

void CmdDialog::abortCommand()
{
    this->close();
}

void CmdDialog::createCmdGroupBox() {
    cmdGroupBox = new QGroupBox(tr("Commands"));

    cmdTypeLabel = new QLabel(tr("Type:"));
    cmdTypeComboBox = new QComboBox;
    //Same order as enum definition (cmdtype)
    // TODO: Iterate over cmdtype and add them
    cmdTypeComboBox->addItem("Bash");
    cmdTypeComboBox->addItem("Python");
    cmdTypeComboBox->setCurrentIndex(0);

    cmdNameLabel = new QLabel(tr("Name:"));
    cmdNameEdit = new QLineEdit(tr("Command"));

    cmdScriptLabel = new QLabel(tr("Script Path:"));
    cmdScriptEdit = new QLineEdit(tr("/path/to/script.sh"));

    cmdSaveButton = new QPushButton(tr("Save"));
    cmdSaveButton->setDefault(true);

    cmdAbortButton = new QPushButton(tr("Abort"));
    cmdAbortButton->setDefault(true);

    QGridLayout *cmdLayout = new QGridLayout;
    cmdLayout->addWidget(cmdTypeLabel, 0, 0);
    cmdLayout->addWidget(cmdTypeComboBox, 0, 1, 1, 2);
    cmdLayout->addWidget(cmdNameLabel, 1, 0);
    cmdLayout->addWidget(cmdNameEdit, 1, 1, 1, 2);
    cmdLayout->addWidget(cmdScriptLabel, 2, 0);
    cmdLayout->addWidget(cmdScriptEdit, 2, 1, 1, 4);
    cmdLayout->addWidget(cmdSaveButton, 3, 0, 1, 1);
    cmdLayout->addWidget(cmdAbortButton, 3, 1, 1, 1);
    cmdLayout->setColumnStretch(4, 1);
    cmdLayout->setRowStretch(5, 1);
    cmdGroupBox->setLayout(cmdLayout);
}

void CmdDialog::createActions()
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

#endif
