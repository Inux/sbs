#ifndef CMDS_H
#define CMDS_H

#include <list>

#include "cmd.h"

namespace Commands {

class Cmds {

public:
    Cmds();
    ~Cmds() = default;
    void add(Cmd cmd);
    void remove(Cmd cmd);

private:
    std::list<Cmd> mCmds;
};

}

#endif // CMDS_H
