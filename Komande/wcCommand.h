#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"

class WcCommand : public Command
{
public:

    WcCommand() : Command(true, true) {} // uzima argumente i uzima opt 

    void execute(char &opt, std::string &argument, std::ostream &output) override;

    std::string getName() const override {
        return "wc";
    }

};

#endif