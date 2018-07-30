#ifndef CMD_H
#define CMD_H

#include "cmdtype.h"

#include <qstring.h>
#include <qdebug.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <qprocess.h>
#include <qtemporaryfile.h>

namespace Commands {

class Cmd
{
public:
    Cmd(CmdType cmdType, QString name, QString scriptPath);
    ~Cmd() = default;
    bool execute(void) const;
    CmdType getCmdType(void) const;
    QString getName(void) const;
    QString getScriptPath(void) const;

    bool operator==(const Cmd& otherCmd) const;
private:
    CmdType mCmdType;
    QString mName;
    QString mScriptPath;
};

}

#endif // CMD_H
