#ifndef CMD_H
#define CMD_H

#include "cmdtype.h"

#include <qvariant.h>
#include <qstring.h>
#include <qdatastream.h>
#include <QtCore/qsettings.h>

namespace Commands {

struct Cmd {
    Commands::CmdType cmdType;
    QString name;
    QString scriptPath;
};

} // nammespace Commands

Q_DECLARE_METATYPE(Commands::Cmd)

#endif // CMD_H
