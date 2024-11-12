#ifndef commandFactory_h
#define commandFactory_h

#include "command.h"
#include "functionsBase.h"
#include <memory>


class CommandFactory
{

public:

    // prima naziv komande i na osnovu njega kreira instancu specificne komande
    // vraca nullptr ako ne odgovara nijednoj poznatoj komandi
    std::unique_ptr<Command> createCommand(const std::string &commandName);

};

#endif
