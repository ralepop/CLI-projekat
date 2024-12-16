#include "Funkc/commandInterpreter.h"
#include "Funkc/commandFactory.h"

#include <iostream>
#include <string>

int main()
{
    const std::string prompt = "$";
    CommandFactory commandFactory;
    
    CommandInterpreter interpreter(commandFactory, prompt);
    
    std::cout << "CLI interpreter - EOF to exit\n";

    interpreter.start();

    return 0;
}
