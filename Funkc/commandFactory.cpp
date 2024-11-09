#include "commandFactory.h"

std::unique_ptr<Command> commandFactory::createCommand(const std::string &commandName)
{

    if(commandName == "echo") return std::make_unique<EchoCommand>();

    return std::unique_ptr<Command>();
}