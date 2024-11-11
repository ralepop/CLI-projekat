#ifndef timeCommand_h
#define timeCommand_h

#include "../Funkc/command.h"
#include <ctime>
#include <iostream>

class TimeCommand : public Command
{
public:

    // referenca: https://en.cppreference.com/w/cpp/chrono/c/tm

    void execute(std::istream &input, std::ostream &output) override;

};

#endif