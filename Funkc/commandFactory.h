#ifndef commandFactory_h
#define commandFactory_h

#include "command.h"
#include "../Komande/echoCommand.h"
#include "../Komande/timeCommand.h"
#include "../Komande/dateCommand.h"
#include "../Komande/touchCommand.h"
#include "../Komande/wcCommand.h"
#include <memory>


class CommandFactory
{

public:

    // prima naziv komande i na osnovu njega kreira instancu specificne komande
    // vrala nullptr ako ne odgovara nijednoj poznatoj komandi
    std::unique_ptr<Command> createCommand(const std::string &commandName);

};

#endif
