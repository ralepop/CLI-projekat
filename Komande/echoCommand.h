#ifndef echoCommand_h
#define echoCommand_h

#include "../Funkc/command.h"

class EchoCommand : public Command {

public:

    EchoCommand() : Command(true){} // true jer prima argumente

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) override;

    std::string getName() const override {
        return "echo";
    }

};

#endif