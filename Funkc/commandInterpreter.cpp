#include "commandInterpreter.h"

void CommandInterpreter::start()
{
    std::string line;
    
    while(true){
        std::cout << prompt << ' ';
        
        if(!std::getline(std::cin, line)){
            std::cout << "\nIzlaz iz CLI-ja...\n";
            break;
        }
        
        std::istringstream lineStream(line); // ovako analiziramo deo po deo unosa
        std::string commandName;
        lineStream >> commandName; // cita prvi deo iz lineStream
        
        auto command = commandFactory.createCommand(commandName);

        if(command){
            command->execute(lineStream, std::cout);
        }else{
            std::cerr << "command not found: " << commandName << std::endl;
        }

    }
}