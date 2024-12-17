#ifndef dateCommand_h
#define dateCommand_h

#include "../Funkc/command.h"
#include <iostream>

class DateCommand : public Command {

public:

    DateCommand() : Command(false) {} // false jer ne prima argumente

    // referenca: https://en.cppreference.com/w/cpp/chrono/c/tm
    
    void execute(char &opt, std::string &argument, std::ostream &output) override;

    std::string getName() const override {
        return "date";
    }
    

};

#endif