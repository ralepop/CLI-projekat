#ifndef wcCommand_h
#define wcCommand_h

#include "../Funkc/command.h"

class WcCommand : public Command
{
public:

    WcCommand() : Command(true, true) {} // uzima argumente i uzima opt 

    void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) override;

    std::string getName() const override {
        return "wc";
    }

    static size_t countingWords(const std::string &line) {
        bool word = false;
        int i = 0;
        for (const char c : line) {
            if (std::isspace(c)) {
                word = false;
            } else if (!word) {
                i++;
                word = true;
            }
        }
        return i;
    }

    static void processOptW(const std::string &text, std::ostream &output, bool &redirectExist);

    static void processOptC(const std::string &text, std::ostream &output, bool &redirectExist);
};

#endif