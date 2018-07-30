#include "cmds.h"

namespace Commands {

Cmds::Cmds() : mCmds() {
}

std::map<QString, Cmd>& Cmds::getCmds() {
    return mCmds;
}

void Cmds::add(Cmd cmd) {
    mCmds.insert(std::pair<QString, Cmd>(cmd.getName(), cmd));
}

void Cmds::remove(Cmd cmd) {
    mCmds.erase(mCmds.find(cmd.getName()));
}

}

