#include "commandFactory.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string &commandName)
{
    if(commandName == "echo") return std::make_unique<EchoCommand>();
    else if(commandName == "time") return std::make_unique<TimeCommand>();
    else if(commandName == "date") return std::make_unique<DateCommand>();
    else if(commandName == "wc") return std::make_unique<WcCommand>();
    else if(commandName == "touch") return std::make_unique<TouchCommand>();
    else return nullptr; // nepoznata komanda
}