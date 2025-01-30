#include "commandFactory.h"

#include <memory>

#include "batchCommand.h"
#include "dateCommand.h"
#include "echoCommand.h"
#include "headCommand.h"
#include "timeCommand.h"
#include "touchCommand.h"
#include "wcCommand.h"
#include "promptCommand.h"
#include "rmCommand.h"
#include "trCommand.h"
#include "truncateCommand.h"


std::unique_ptr<Command> CommandFactory::createCommand(const std::string &commandName){
    if(commandName == "echo") return std::make_unique<EchoCommand>();
    if(commandName == "time") return std::make_unique<TimeCommand>();
    if(commandName == "date") return std::make_unique<DateCommand>();
    if(commandName == "wc") return std::make_unique<WcCommand>();
    if(commandName == "touch") return std::make_unique<TouchCommand>();
    if(commandName == "prompt") return std::make_unique<PromptCommand>();
    if(commandName == "truncate") return std::make_unique<TruncateCommand>();
    if(commandName == "rm") return std::make_unique<RmCommand>();
    if(commandName == "tr") return std::make_unique<TrCommand>();
    if(commandName == "head") return std::make_unique<HeadCommand>();
    if(commandName == "batch") return std::make_unique<BatchCommand>();
    return nullptr; // nepoznata komanda
}
