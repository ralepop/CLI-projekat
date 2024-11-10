#ifndef commandFactory_h
#define commandFactory_h

#include "command.h"

class commandFactory
{
public:

    std::unique_ptr<Command> createCommand(const std::string &commandName);

    // ovo je izmena od kuce

};

#endif