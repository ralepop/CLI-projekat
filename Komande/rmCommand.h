#ifndef rmCommand_h
#define rmCommand_h

#include "../Funkc/command.h"

class RmCommand : public Command {

public:

    RmCommand() : Command(true){} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) override;

    std::string getName() const override {
        return "rm";
    }

};

#endif