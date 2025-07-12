#ifndef commandFactory_h
#define commandFactory_h

#include "command.h"

#include <memory>

class CommandFactory {

public:

    // prima naziv komande i na osnovu njega kreira instancu specificne komande
    // vraca nullptr ako ne odgovara nijednoj poznatoj komandi
    // std::make_unique automatski upravlja memorijom i sprecava curenje memorije
    static std::unique_ptr<Command> createCommand(const std::string &commandName);

};

#endif
