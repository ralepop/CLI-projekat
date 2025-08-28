#ifndef echoCommand_h
#define echoCommand_h

#include "../Funkc/command.h"

class EchoCommand : public Command {

public:

    EchoCommand() : Command(true) {} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "echo"; }

};

#endif