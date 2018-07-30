#ifndef CMDS_H
#define CMDS_H

#include "cmd.h"

#include <map>
#include <qstring.h>

namespace Commands {

class Cmds {

public:
    Cmds();
    ~Cmds() = default;
    std::map<QString, Cmd>& getCmds();
    void add(Cmd cmd);
    void remove(Cmd cmd);

private:
    std::map<QString, Cmd> mCmds;
};

}

#endif // CMDS_H
