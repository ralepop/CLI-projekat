#include "commandFactory.h"

#include <memory>

#include "dateCommand.h"
#include "echoCommand.h"
#include "timeCommand.h"
#include "touchCommand.h"
#include "wcCommand.h"
#include "promptCommand.h"
#include "truncateCommand.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string &commandName) {
    if (commandName == "echo") return std::make_unique<EchoCommand>();
    if (commandName == "time") return std::make_unique<TimeCommand>();
    if (commandName == "date") return std::make_unique<DateCommand>();
    if (commandName == "wc") return std::make_unique<WcCommand>();
    if (commandName == "touch") return std::make_unique<TouchCommand>();
    if (commandName == "prompt") return std::make_unique<PromptCommand>();
    if (commandName == "truncate") return std::make_unique<TruncateCommand>();
    return nullptr; // nepoznata komanda
}
