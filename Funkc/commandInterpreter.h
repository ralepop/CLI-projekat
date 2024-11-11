#include <string>
#ifndef commandInterpreter_h
#define commandInterpreter_h

#include "commandFactory.h"
#include <sstream>

// upravlja unosom korisnika, pozivanjem odgovarajucih komandi i prosledjivanjem izlaza

class CommandInterpreter
{
private:
    
    CommandFactory &commandFactory;

    std::string prompt = "$"; // korisnik ga moze menjati


public:

    // konstruktor
    CommandInterpreter(CommandFactory &t_commandFactory) : commandFactory(t_commandFactory) {};

    // start() pokrece glavnu petlju za unos i izvrsavanje komandi
    void start();

};

#endif