#include "cmd.h"

namespace {
    bool fileExists(QString path) {
        QFileInfo check_file(path);
        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile()) {
            return true;
        } else {
            return false;
        }
    }

    QString getBash() {
        return "/bin/sh";
    }

    QString getPython() {
        return "/Users/inux/miniconda3/bin/python3";
    }

    bool execute(const QString& executeable, const QStringList& args) {
        QProcess proc;
        proc.start(executeable, args);
        proc.waitForFinished(-1);
        QString output(proc.readAllStandardOutput());
        QString error(proc.readAllStandardError());

        qDebug() << "Command Output: " << output;
        qDebug() << "Command Error: " << error;

        if(proc.exitStatus() == QProcess::ExitStatus::NormalExit) {
            return true;
        } else {
            return false;
        }
    }
}

namespace Commands {

Cmd::Cmd(CmdType cmdType, QString name, QString scriptPath) :
    mCmdType(cmdType), mName(name), mScriptPath(scriptPath)
{
    mCmdType = cmdType;
    mName = name;
    mScriptPath = scriptPath;
}

bool Cmd::execute() const {
    if(fileExists(mScriptPath)) {
        QFile file(mScriptPath);
        QTemporaryFile *tempFile = QTemporaryFile::createNativeFile(file);
        QStringList args;
        args << tempFile->fileName();

        switch(mCmdType) {
            case Commands::BASH:
                ::execute(getBash(), args);
            break;
            case Commands::PYTHON:
                ::execute(getPython(), args);
            break;
        }
        tempFile->remove();
    } else {
        qDebug() << mScriptPath << "doesn't exist!";
    }
    return true;
}

CmdType Cmd::getCmdType() const {
    return mCmdType;
}

QString Cmd::getName() const {
    return mName;
}


QString Cmd::getScriptPath() const {
    return mScriptPath;
}

bool Cmd::operator==(const Cmd& otherCmd) const {
    return (mCmdType == otherCmd.getCmdType() &&
            mName == otherCmd.getName() &&
            mScriptPath == otherCmd.getScriptPath());
}

}
