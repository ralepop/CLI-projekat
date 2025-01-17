#ifndef timeCommand_h
#define timeCommand_h

#include "../Funkc/command.h"
#include <iostream>

class TimeCommand : public Command
{
public:

    TimeCommand() : Command(false) {} // false jer ne prima argumente

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) override;

    std::string getName() const override {
        return "time";
    }

};

#endif