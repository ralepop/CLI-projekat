#ifndef touchCommand_h
#define touchCommand_h

#include "../Funkc/command.h"

class TouchCommand : public Command {
    
public:

    TouchCommand() : Command(true) {} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "touch"; }

};

#endif
