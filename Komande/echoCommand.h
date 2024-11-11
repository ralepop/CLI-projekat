#ifndef echoCommand_h
#define echoCommand_h

#include "../Funkc/command.h"

class EchoCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override;

};

#endif