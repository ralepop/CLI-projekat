#ifndef rmCommand_h
#define rmCommand_h

#include "../Funkc/command.h"

class RmCommand : public Command {

public:

    RmCommand() : Command(true) {} // true jer prima argumente

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) override;

    std::string getName() const override {
        return "rm";
    }

};

#endif