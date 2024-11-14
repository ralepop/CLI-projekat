#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"
#include <iostream>
#include <cctype>


class WcCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override;

};

#endif