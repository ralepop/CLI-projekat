#ifndef timeCommand_h
#define timeCommand_h

#include <ctime>

#include "../Funkc/command.h"

class TimeCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);

        // referenca: https://en.cppreference.com/w/cpp/chrono/c/tm
    }

};

#endif