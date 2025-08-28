#ifndef headCommand_h
#define headCommand_h

#include "../Funkc/command.h"

class HeadCommand : public Command {

public:

    HeadCommand() : Command(true, true) {} // true jer prima argumente i true jer prima -ncount(nazvano je opt ali gledamo kao -ncount)

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "head"; }

};

#endif