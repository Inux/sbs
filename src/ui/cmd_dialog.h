#ifndef CMD_DIALOG_H
#define CMD_DIALOG_H

#include <QDialog>
#include <QDebug>
#include <qlogging.h>

#include "cmd_manager.h"

class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

class CmdDialog : public QDialog
{
    Q_OBJECT

public:
    CmdDialog();

    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void saveCommand();
    void abortCommand();

private:
    void createCmdGroupBox();
    void createActions();

    QGroupBox* cmdGroupBox;
    QLabel* cmdTypeLabel;
    QComboBox *cmdTypeComboBox;
    QLabel* cmdNameLabel;
    QLineEdit* cmdNameEdit;
    QLabel* cmdScriptLabel;
    QLineEdit* cmdScriptEdit;
    QPushButton* cmdSaveButton;
    QPushButton* cmdAbortButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
};

#endif // CMD_DIALOG_H
