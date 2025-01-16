#ifndef trCommand_h
#define trCommand_h

#include "../Funkc/command.h"

class TrCommand : public Command {

public:

    TrCommand() : Command(true, true) {} // true jer prima argumente i true jer prima [with] (nazvano je opt ali gledamo kao [with])

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) override;

    std::string getName() const override {
        return "tr";
    }

};

#endif