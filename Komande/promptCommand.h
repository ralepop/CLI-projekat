#ifndef promptCommand_h
#define promptCommand_h

#include "../Funkc/command.h"

class PromptCommand : public Command {

public:

    PromptCommand() : Command(true){} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "prompt"; }

};

#endif