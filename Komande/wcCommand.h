#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"
#include <cctype>
#include <fstream>


class WcCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override;

};

#endif