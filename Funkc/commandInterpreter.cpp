#include "commandInterpreter.h"

#include <sstream>

constexpr size_t MAX_LINE_SIZE = 512;

void CommandInterpreter::start(){

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

        if (command->doesTakeOpt() && commandName != "tr") {
            inputStream >> opt;
        }

        std::getline(inputStream, arg);
        Command::stripWhitespace(arg);

        if (arg.empty() && command->doesTakeArg()) {
            std::string additionalLine;
            while (true) {
                std::getline(std::cin, additionalLine);
                if (additionalLine.empty()) break;
                arg += (arg.empty() ? "" : "\n") + additionalLine;
            }
        }

        if (command->getName() == "prompt") {
            if (!arg.empty()) {
                prompt = arg;
            }
            continue;
        }

        bool rediExist = Command::redirectExist(inputLine);


        command->execute(opt[1], arg, std::cout, rediExist);

    }

}
