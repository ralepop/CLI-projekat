#include "commandInterpreter.h"

#include <sstream>
#include <string>
#include <vector>

constexpr size_t MAX_LINE_SIZE = 512;

void CommandInterpreter::start() {

    while (true) {
        std::cout << prompt << ' ';
        bool pipeExist = false;

        // citamo celu liniju
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if (inputLine.empty()) break;

        if (inputLine.length() > MAX_LINE_SIZE) inputLine = inputLine.substr(0, MAX_LINE_SIZE);

        std::vector<std::string> inputs;

        if (Command::pipeExist(inputLine)) {
            inputs = Command::splitString(inputLine, '|');
            pipeExist = true;
        } 
        else inputs.push_back(inputLine);

        std::string lastResult;

        std::ostream& output = std::cout;

        Command::processCommand(inputs, inputLine, prompt, output, lastResult, pipeExist);
        
    }

}
