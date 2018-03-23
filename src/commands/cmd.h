#ifndef CMD_H
#define CMD_H

#include <string>

#include "cmdtype.h"

namespace Commands {

class Cmd
{
public:
    Cmd(std::string name, std::string scriptPath, CmdType cmdType);
    ~Cmd() = default;
    bool execute(void);
    std::string getName(void) const;
    std::string getScriptPath(void) const;
    CmdType getCmdType(void) const;

    bool operator==(const Cmd& otherCmd) const;
private:
    std::string mName;
    std::string mScriptPath;
    CmdType mCmdType;
};

}

#endif // CMD_H
