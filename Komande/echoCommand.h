#ifndef echoCommand_h
#define echoCommand_h

#include "../Funkc/command.h"

class EchoCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override {
        std::string line;
        std::getline(input, line);
        output << line << std::endl;
    }

};

#endif