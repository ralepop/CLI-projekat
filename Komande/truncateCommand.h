#ifndef truncateCommand_h
#define truncateCommand_h

#include "../Funkc/command.h"

class TruncateCommand : public Command {

public:

    TruncateCommand() : Command(true) {} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;

    std::string getName() const override { return "truncate"; }

};

#endif