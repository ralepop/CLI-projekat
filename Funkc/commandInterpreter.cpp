#include "commandInterpreter.h"

#include <iostream>
#include <string>
#include <vector>

void CommandInterpreter::start() {
    
    std::string line;
    std::string commandName;
    char opt = '\0';
    std::string argument;

    int zapamti;
    int poz;

    while (std::cout << prompt << ' ' && std::getline(std::cin, line)) {

        commandName = Command::commandName(line);

        auto command = CommandFactory::createCommand(commandName);

        if (command) {

            if(command->doesTakeOpt()){ // ako nasa komanda uzima -opt
                opt = Command::opt(line);
            }
            
            if (command->doesTakeArg()) { // ukoliko nasa komanda prihvata argumente
            
                if (!line.empty()) { // ukoliko argument postoji
                    
                    argument = line;
                    command->execute(opt, argument, std::cout);

                } else if(line.empty() || line == "\0") { // ukoliko argument ne postoji

                    std::vector<std::string> argumenti;

                    while (std::getline(std::cin, argument)) {
                        
                        if (argument.empty()) break;
                        argumenti.push_back(argument);

                    }

                    for (auto& argu : argumenti) {
                        command->execute(opt, argu, std::cout);
                    }

                }

            } else { // ukoliko nasa komanda ne prihvata argumente 

                argument.clear();
                command->execute(opt, argument, std::cout);

            }
            

        } else {
            std::cout << "Unknown command: " << commandName << std::endl;
        }
    }
}