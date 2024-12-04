#include "commandInterpreter.h"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

void CommandInterpreter::start()
{
    std::string line {};
    std::string commandName {};
    std::string argument {};
    int zapamti {};
    bool argumentExist {false};
    bool isNoArgFunction {false};

    while (std::cout << prompt << ' ' && std::getline(std::cin, line)) {

        argumentExist = Command::argumentExist(line, zapamti); // proverava da li je argument unet

        commandName = line.substr(0, (argumentExist) ? zapamti : line.length());

        auto command = CommandFactory::createCommand(commandName);

        

        if (command) {
            
            if(command->doesTakeArg()) { // ukoliko nasa komanda prihvata argumente

                if(argumentExist) { // ukoliko argument postoji

                    argument = line.substr(zapamti + 1, line.length());
                    command->execute(argument, std::cout);
                    continue;

                }else{ // ukoliko argument ne postoji
                    
                    std::vector<std::string> argumenti {};
                    
                    while (std::getline(std::cin, argument)) {

                        if (argument.empty()) break;
                        argumenti.push_back(argument);

                    }

                    for (auto& argu : argumenti) {
                        command->execute(argu, std::cout);
                    }
                }
            }else{ // ukoliko nasa komanda ne prihvata argumente
                argument.clear();
                command->execute(argument, std::cout);
            }

        } else {
            std::cout << "Unknown command: " << commandName << std::endl;
        }
    }
}