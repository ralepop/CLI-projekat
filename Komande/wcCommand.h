#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"
#include <fstream>

class WcCommand : public Command
{
public:

    void execute(std::string &argument, std::ostream &output) override;

};

#endif