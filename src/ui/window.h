#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QDebug>
#include <qlogging.h>

#include "cmdresult.h"
#include "cmdmanager.h"

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
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void executeCommand();
    void messageClicked();

private:
    void createCommands();
    void createIconGroupBox();
    void createMessageGroupBox();
    void createCmdGroupBox();
    void createActions();
    void createTrayIcon();

    QGroupBox *iconGroupBox;
    QLabel *iconLabel;
    QComboBox *iconComboBox;
    QCheckBox *showIconCheckBox;
    QPushButton *executeCommandButton;

    QGroupBox *messageGroupBox;
    QLabel *typeLabel;
    QLabel *durationLabel;
    QLabel *durationWarningLabel;
    QLabel *titleLabel;
    QLabel *bodyLabel;
    QComboBox *typeComboBox;
    QSpinBox *durationSpinBox;
    QLineEdit *titleEdit;
    QTextEdit *bodyEdit;
    QPushButton *showMessageButton;

    QGroupBox* cmdGroupBox;
    QLabel* cmdTypeLabel;
    QComboBox *cmdTypeComboBox;
    QLabel* cmdNameLabel;
    QLineEdit* cmdNameEdit;
    QLabel* cmdScriptLabel;
    QLineEdit* cmdScriptEdit;
    QPushButton* cmdSaveButton;

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
