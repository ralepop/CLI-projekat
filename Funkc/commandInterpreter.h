#include <string>
#ifndef commandInterpreter_h
#define commandInterpreter_h

#include "commandFactory.h"

// ova klasa upravlja celokupnim tokom interpretera
// cita unos i izvrsava komande

class commandInterpreter
{
private:

    std::string prompt = "$"; // korisnik ga moze menjati

    CommandFactory CommandFactory;

protected:



public:



};

#endif