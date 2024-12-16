#include "commandInterpreter.h"
#include "command.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

void CommandInterpreter::start() const {
    char commandName[10] {};
    char opt[3] {};

    while (std::cout << prompt << ' ' && std::cin >> commandName) {


        if (auto command = CommandFactory::createCommand(std::string(commandName))) {

            if (command->doesTakeOpt()) { // ako nasa funkcija uzima opt
                std::cin >> opt;
            }

            if (command->doesTakeArg()) { // ako nasa funkcija uzima arg

                char argument[500] {};
                
                std::cin.getline(argument, sizeof(argument));

                std::string arg(argument);

                if (!arg.empty()) {

                    command->execute(opt[1], arg, std::cout);

                } else {

                    std::vector<std::string> arguments;

                    while (std::getline(std::cin, arg) && !arg.empty()) {
                        arguments.push_back(arg);
                    }

                    for (auto& arg : arguments) {
                        command->execute(opt[1], arg, std::cout);
                    }
                }
            } else { // ako nasa funkcija ne uzima arg
                std::string prazan;
                command->execute(opt[1], prazan, std::cout);
            }
        } else {
            std::cout << "Un§known command: " << commandName << std::endl;
        }
    }
}