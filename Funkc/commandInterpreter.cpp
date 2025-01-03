#include "commandInterpreter.h"

#include <sstream>

constexpr size_t MAX_LINE_SIZE = 10;

void CommandInterpreter::start() const {

    while (true) {
        std::cout << prompt << ' ';

        // citamo celu liniju
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if (inputLine.empty()) break;

        if (inputLine.length() > MAX_LINE_SIZE) {
            inputLine = inputLine.substr(0, MAX_LINE_SIZE);
        }

        // uzimamo commandName
        std::istringstream inputStream(inputLine);
        std::string commandName;
        inputStream >> commandName;

        const auto command = CommandFactory::createCommand(commandName);

        if (!command) {
            if (Command::errorHandling(inputLine)) {
                std::cout << "Error: Unknown command \"" << commandName << "\".\n";
            }
            continue;
        }

        std::string opt;
        std::string arg;

        if (command->doesTakeOpt()) {
            inputStream >> opt;
        }

        std::getline(inputStream, arg);
        Command::stripWhitespace(arg);

        command->execute(opt[1], arg, std::cout);

    }

}
