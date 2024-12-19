#include "commandInterpreter.h"
#include "command.h"
#include <string>
#include <iostream>
#include <cstring>


void CommandInterpreter::start() const {
    char commandName[10] {};
    char opt[3] {};
    char argument[500] {};


    std::string ost;

    while (std::cout << prompt << ' ' && std::cin >> commandName) {

        std::string line = std::string(commandName);

        auto command = CommandFactory::createCommand(std::string(commandName));

        if (!command) {

            std::getline(std::cin, ost);
            line += ost;

            if (Command::errorHandling(line)) {
                std::cout << "Error: Unknown command " << commandName << '\n';
            }

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
        

    }
}