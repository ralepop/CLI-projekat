#ifndef echoCommand_h
#define echoCommand_h

#include "../Funkc/command.h"

class EchoCommand : public Command {

public:

    void execute(char &opt, std::string &argument, std::ostream &output) override;

};

#endif