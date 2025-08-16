#ifndef batchCommand_h
#define batchCommand_h

#include "../Funkc/command.h"

class BatchCommand : public Command {

public:

    BatchCommand() : Command(true){} // true jer prima argumente

    void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) override;
    
    inline std::string getName() const override { return "batch"; }

};

#endif