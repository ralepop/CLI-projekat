#ifndef timeCommand_h
#define timeCommand_h

#include "../Funkc/command.h"
#include <iostream>

class TimeCommand : public Command
{
public:

    TimeCommand() : Command(false){} // false jer ne prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) override;

    std::string getName() const override {
        return "time";
    }

};

#endif