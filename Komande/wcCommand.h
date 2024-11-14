#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"
#include <iostream>
#include <cctype>


class WcCommand : public Command
{
public:

    void execute(std::istream &input, std::ostream &output) override;
    
    // enum Mod { WORDS, CHAR };

    // WcCommand(Mod t_mode) : mode(t_mode) {}

    // int count(const std::string& text) const;

private:

    // Mod mode;

};

#endif