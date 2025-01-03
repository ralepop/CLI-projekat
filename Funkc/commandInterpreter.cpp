#include "commandInterpreter.h"
#include "command.h"
#include <string>
#include <iostream>
#include <cstring>


void CommandInterpreter::start() const {


    while (true) {

        char commandName[9] {};
        char opt[3] {};
        // char argument[500] {};
        std::cout << prompt << ' ';
        std::cin >> commandName;

        if (commandName[0] == '\0') break;

        std::string line = std::string(commandName);

        const auto command = CommandFactory::createCommand(std::string(commandName));

        if (!command) {
            std::string ost;

            std::getline(std::cin, ost);
            line += ost;

            if (Command::errorHandling(line)) {
                std::cout << "Error: Unknown command " << commandName << '\n';
            }

        } else {

            std::string arg;
            size_t argSize;
            if (command->doesTakeOpt()) {
                std::cin >> opt;
                line += " " + std::string(opt);
                argSize = 513 - std::strlen(commandName) - std::strlen(opt);
            } else {
                argSize = 513 - std::strlen(commandName);
            }


            char* argument = new char[argSize]();

            std::cin.getline(argument, argSize);

            size_t chrArgSize = std::strlen(argument);

            line += std::string(argument);
            arg += std::string(argument);

            Command::stripWhitespace(arg);
            command->execute(opt[1], arg, std::cout);


            delete[] argument;
        }

    }
}