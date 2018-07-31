#ifndef CMDRESULT_H
#define CMDRESULT_H

#include <qstring.h>

namespace Commands
{

struct CmdResult {
    bool result;
    QString output;
    QString errors;
};

} // namespace Commands

#endif // CMDRESULT_H
