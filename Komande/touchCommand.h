#ifndef touchCommand_h
#define touchCommand_h

#include "../Funkc/command.h"


class TouchCommand : public Command
{
public:

    void execute(char &opt, std::string &argument, std::ostream &output) override;

    std::string getName() const override {
        return "touch";
    }

};

#endif
