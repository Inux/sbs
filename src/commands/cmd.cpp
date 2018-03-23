#include "cmd.h"

using namespace Commands;

Cmd::Cmd(std::string name, std::string scriptPath, CmdType cmdType) :
    mName(name), mScriptPath(scriptPath), mCmdType(cmdType)
{

}

bool Cmd::execute() {
    return true;
}

std::string Cmd::getName() const {
    return this->mName;
}


std::string Cmd::getScriptPath() const {
    return this->mScriptPath;
}

CmdType Cmd::getCmdType() const {
    return this->mCmdType;
}

bool Cmd::operator==(const Cmd& otherCmd) const {
    return (this->mName == otherCmd.getName() &&
            this->mScriptPath == otherCmd.getScriptPath() &&
            this->mCmdType == otherCmd.getCmdType());
}
