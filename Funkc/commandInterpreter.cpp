#include "commandInterpreter.h"

void CommandInterpreter::start()
{
    std::string line {};
    

    while(true){
        std::cout << prompt << ' ';
        
        if(!std::getline(std::cin, line)) break;
        
        std::istringstream lineStream{line}; // analiziramo deo po deo unosa
        std::string commandName {};
        lineStream >> commandName; // cita prvi deo iz lineStream
        
        auto command = CommandFactory::createCommand(commandName);

        if(command){
            command->execute(lineStream, std::cout);
        }else{
            std::cout << "Unknown command: " << commandName << std::endl;
        }

    }
}