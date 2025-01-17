#ifndef promptCommand_h
#define promptCommand_h

#include "../Funkc/command.h"

class PromptCommand : public Command {

public:

    PromptCommand() : Command(true) {} // true jer prima argumente

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) override;

    std::string getName() const override {
        return "prompt";
    }


};

#endif