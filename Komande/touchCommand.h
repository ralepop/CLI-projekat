#ifndef touchCommand_h
#define touchCommand_h

#include "../Funkc/command.h"
#include <fstream>
#include <iostream>

class TouchCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override;

};

#endif
