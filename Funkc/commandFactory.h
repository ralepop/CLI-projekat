#ifndef commandFactory_h
#define commandFactory_h

#include "command.h"
#include "functionsBase.h"

class CommandFactory
{

public:

    // prima naziv komande i na osnovu njega kreira instancu specificne komande
    // vraca nullptr ako ne odgovara nijednoj poznatoj komandi
    // unique_ptr je pogodan jer brise sam objekat kada se vise ne koristi
    static std::unique_ptr<Command> createCommand(const std::string &commandName);

};

#endif
