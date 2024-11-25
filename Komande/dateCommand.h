#ifndef dateCommand_h
#define dateCommand_h

#include "../Funkc/command.h"
#include <iostream>

class DateCommand : public Command
{
public:

    // referenca: https://en.cppreference.com/w/cpp/chrono/c/tm
    
    void execute(std::istream &input, std::ostream &output) override;

};

#endif