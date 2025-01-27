#ifndef headCommand_h
#define headCommand_h

#include "../Funkc/command.h"

class HeadCommand : public Command {

public:

    HeadCommand() : Command(true, true){} // true jer prima argumente i true jer prima [with](nazvano je opt ali gledamo kao [with])

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) override;
    

    std::string getName() const override {
        return "head";
    }

};

#endif