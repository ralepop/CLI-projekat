#include "commandInterpreter.h"
#include "command.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

void CommandInterpreter::start() const {
    char commandName[10] {};
    char opt[3] {};
    char argument[500] {};

    char errorPositions[512] {};

    std::string line;
    std::string ost;

    while (std::cout << prompt << ' ' && std::cin >> commandName) {
        
        line = std::string(commandName);

        auto command = CommandFactory::createCommand(std::string(commandName));

        if (!command) {

            std::getline(std::cin, ost);
            line += ost;


        } else {

            if (command->doesTakeOpt()) {
                std::cin >> opt;
                line += " " + std::string(opt);
            }

            if (command->doesTakeArg()) {

                std::cin.getline(argument, sizeof(argument));

                line += std::string(argument);
            }

            std::string arg(argument);

            command->execute(opt[1], arg, std::cout);

        }
        
        Command::errorHandling(line);

    }
}