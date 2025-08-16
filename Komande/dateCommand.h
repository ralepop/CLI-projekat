#ifndef dateCommand_h
#define dateCommand_h

#include "../Funkc/command.h"

class DateCommand : public Command {

public:

    DateCommand() : Command(false){} // false jer ne prima argumente

    // referenca: https://en.cppreference.com/w/cpp/chrono/c/tm
    
    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "date"; }

};

#endif