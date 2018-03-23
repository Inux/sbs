#include "cmds.h"

using namespace Commands;

Cmds::Cmds() {
}

void Cmds::add(Cmd cmd) {
    this->mCmds.push_back(cmd);
}

void Cmds::remove(Cmd cmd) {
    this->mCmds.remove(cmd);
}

