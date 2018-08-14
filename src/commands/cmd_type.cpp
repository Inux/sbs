#include "cmd_type.h"

namespace Commands {

const QString getTypeString(Commands::CmdType cmdType) {
    switch(cmdType) {
        case Commands::CmdType::BASH:
            return "Bash";
        break;
        case Commands::CmdType::PYTHON:
            return "Python";
        break;
        case Commands::CmdType::UNKNOWN:
        default:
            return "Unknown";
        break;
    }
    return "Unknown";
}

}; // namespace Commands
