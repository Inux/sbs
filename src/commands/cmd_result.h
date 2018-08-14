#ifndef CMD_RESULT_H
#define CMD_RESULT_H

#include <qstring.h>

namespace Commands
{

struct CmdResult {
    bool result;
    QString output;
    QString errors;
};

} // namespace Commands

#endif // CMD_RESULT_H
