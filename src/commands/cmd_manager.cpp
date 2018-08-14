#include "cmd_manager.h"

const QString CONFIG_UPDATE_DATE = "updateDate";
const QString CONFIG_COMMAND_NAMES = "commandNames";

namespace
{
bool fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if it is directory
    if (check_file.exists() && check_file.isFile())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString getBash()
{
    return "/bin/sh";
}

QString getPython()
{
    return "/Users/inux/miniconda3/bin/python3";
}

Commands::CmdResult execute(const QString &executeable, const QStringList &args)
{
    QProcess proc;
    proc.start(executeable, args);
    proc.waitForFinished(-1);
    QString output(proc.readAllStandardOutput());
    QString error(proc.readAllStandardError());

    qDebug() << "Command Output: " << output;
    qDebug() << "Command Error: " << error;

    if (proc.exitStatus() == QProcess::ExitStatus::NormalExit)
    {
        return {true, output, error};
    }
    else
    {
        return {false, output, error};
    }
}
} // namespace

namespace Commands
{

CmdManager::CmdManager() : commands()
{
}

std::map<QString, Cmd> CmdManager::getCmds()
{
    return commands;
}

std::pair<const QString, Cmd> CmdManager::getCmdByIndex(const int index)
{
    int count = 0;
    for(auto& c : this->getCmds()) {
        if(count == index)
        {
            return c;
        }
        count++;
    }
    auto retval = std::pair<const QString, Cmd>();
    return retval;
}

void CmdManager::add(Cmd cmd)
{
    commands.insert(std::pair<QString, Cmd>(cmd.name, cmd));
}

void CmdManager::remove(Cmd cmd)
{
    commands.erase(commands.find(cmd.name));
}

CmdResult CmdManager::execute(QString cmdKey)
{
    CmdResult retval = {true, "", ""};
    auto pos = commands.find(cmdKey);
    if (pos == commands.end())
    {
        retval = {false, QString("no output"), QString("Couldn't find command: " + cmdKey)};
    }
    Cmd cmd = pos->second;
    if (fileExists(cmd.scriptPath))
    {
        QFile file(cmd.scriptPath);
        QTemporaryFile *tempFile = QTemporaryFile::createNativeFile(file);
        QStringList args;
        args << tempFile->fileName();

        switch (cmd.cmdType)
        {
        case Commands::BASH:
            retval = ::execute(getBash(), args);
            break;
        case Commands::PYTHON:
            retval = ::execute(getPython(), args);
            break;
        case Commands::UNKNOWN:
            retval = {false, QString("no output"), QString("Command type is UNKNOWN")};
            break;
        }
        tempFile->remove();
    }
    else
    {
        if(retval.result) {
            retval = {false, QString("no output"), QString("Couldn't find script: " + cmd.scriptPath)};
        }
    }
    return retval;
}

void CmdManager::saveSettings(void) {
    QSettings s;

    QList<QString> commandNames;
    for(auto& pair : commands) {
        commandNames.push_back(pair.first);
        qDebug() << "Saving Command:" << pair.first << "as" << pair.first.trimmed();
        s.setValue(pair.first.trimmed(), QVariant::fromValue(pair.second));
        qDebug() << "Type:" << pair.second.cmdType;
        qDebug() << "Name:" << pair.second.name;
        qDebug() << "Script:" << pair.second.scriptPath;
    }
    s.setValue(CONFIG_UPDATE_DATE, QDate::currentDate().toString());
    s.setValue(CONFIG_COMMAND_NAMES, QVariant::fromValue(commandNames));
    s.sync();
}

void CmdManager::loadSettings(void) {
    commands.clear();
    QSettings s;
    QVariant cmdsVariant = s.value(CONFIG_COMMAND_NAMES);
    QList<QString> commandNames = cmdsVariant.value<QList<QString>>();
    for(auto commandName : commandNames) {
        if(commandName != nullptr && commandName != "") {
            qDebug() << "Found Command:" << commandName;
            QVariant cmdVariant = s.value(commandName);
            Commands::Cmd cmd = cmdVariant.value<Commands::Cmd>();
            qDebug() << "Type:" << cmd.cmdType;
            qDebug() << "Name:" << cmd.name;
            qDebug() << "Script:" << cmd.scriptPath;
            commands.insert(std::pair<QString, Cmd>(cmd.name, cmd));
        }
    }
    QVariant lastUpdate = s.value(CONFIG_UPDATE_DATE);
    qDebug() << "Config last update:" << lastUpdate.value<QString>();
}

} // namespace Commands
