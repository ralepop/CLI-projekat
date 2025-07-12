#include "commandFactory.h"

#include "batchCommand.h"
#include "dateCommand.h"
#include "echoCommand.h"
#include "headCommand.h"
#include "promptCommand.h"
#include "rmCommand.h"
#include "timeCommand.h"
#include "touchCommand.h"
#include "trCommand.h"
#include "truncateCommand.h"
#include "wcCommand.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string &commandName){
    if(commandName == "batch") return std::make_unique<BatchCommand>();
    if(commandName == "date") return std::make_unique<DateCommand>();
    if(commandName == "echo") return std::make_unique<EchoCommand>();
    if(commandName == "head") return std::make_unique<HeadCommand>();
    if(commandName == "prompt") return std::make_unique<PromptCommand>();
    if(commandName == "rm") return std::make_unique<RmCommand>();
    if(commandName == "time") return std::make_unique<TimeCommand>();
    if(commandName == "touch") return std::make_unique<TouchCommand>();
    if(commandName == "tr") return std::make_unique<TrCommand>();
    if(commandName == "truncate") return std::make_unique<TruncateCommand>();
    if(commandName == "wc") return std::make_unique<WcCommand>();
    return nullptr; // nepoznata komanda
}
