#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QDebug>
#include <qlogging.h>

#include "cmd_result.h"
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

class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setCmdOfEditor(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void showCmdDialog();
    void executeCommand();
    void messageClicked();

private:
    void createCommands();
    void createCmdSelectGroupBox();
    void createCmdGroupBox();
    void createActions();
    void createTrayIcon();

    QGroupBox *cmdSelectGroupBox;
    QLabel *cmdSelectLabel;
    QComboBox *cmdSelectComboBox;
    QPushButton *executeCommandButton;

    QGroupBox* cmdGroupBox;
    QLabel* cmdTypeLabel;
    QLineEdit *cmdTypeEdit;
    QLabel* cmdNameLabel;
    QLineEdit* cmdNameEdit;
    QLabel* cmdScriptLabel;
    QLineEdit* cmdScriptEdit;
    QLabel* cmdNewLabel;
    QPushButton* cmdNewButton;
    QPushButton* cmdDeleteButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    Commands::CmdManager* cmdManager;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
