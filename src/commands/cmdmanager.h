#ifndef CMDMANAGER_H
#define CMDMANAGER_H

#include "cmd.h"
#include "cmdresult.h"

#include <map>
#include <qdebug.h>
#include <qlist.h>
#include <qstring.h>
#include <QDate>
#include <qfileinfo.h>
#include <qprocess.h>
#include <qtemporaryfile.h>

namespace Commands {

class CmdManager
{

public:
    CmdManager();
    ~CmdManager() = default;
    std::map<QString, Cmd>& getCmds();
    void add(Cmd cmd);
    void remove(Cmd cmd);
    CmdResult execute(QString cmdKey);
    void saveSettings(void);
    void loadSettings(void);

private:
    std::map<QString, Cmd> commands;

};

} // namespace Commands

#endif // CMDMANAGER_H
