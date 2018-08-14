#ifndef CMD_TYPE_H
#define CMD_TYPE_H

#include <QString>

namespace Commands {

typedef enum : unsigned int
{
    BASH,
    PYTHON,
    UNKNOWN
} CmdType;

const QString getTypeString(Commands::CmdType cmdType);

}; // namespace Commands

#endif // CMD_TYPE_H
