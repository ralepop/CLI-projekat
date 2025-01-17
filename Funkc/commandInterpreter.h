#ifndef commandInterpreter_h
#define commandInterpreter_h

#include "commandFactory.h"

// upravlja unosom korisnika, pozivanjem odgovarajucih komandi i prosledjivanjem izlaza

class CommandInterpreter {

private:

    CommandFactory &commandFactory;

    std::string prompt; // korisnik ga moze menjati

public:

    // konstruktor
    CommandInterpreter(CommandFactory &t_commandFactory, std::string t_prompt = "$") :
    commandFactory(t_commandFactory),
    prompt(t_prompt)
    {};

    // pokrece glavnu petlju za unos i izvrsavanje komandi
    void start();

    void setPrompt(const std::string &p) {
        prompt = p;
    }

};

#endif