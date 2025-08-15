#include "commandInterpreter.h"

#include <sstream>
#include <string>
#include <vector>

constexpr size_t MAX_LINE_SIZE = 512;

void CommandInterpreter::start(){

    while(true){
        std::cout << prompt << ' ';

        // citamo celu liniju
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if(inputLine.empty()) break;

        if(inputLine.length() > MAX_LINE_SIZE) inputLine = inputLine.substr(0, MAX_LINE_SIZE);

        std::vector<std::string> inputs;

        if(Command::pipeExist(inputLine)) inputs = Command::splitString(inputLine, '|');
        else inputs.push_back(inputLine);

        // TODO: proveri da li je outputBuffer neophodan ili moze samo lastResult da radi
        std::ostringstream outputBuffer; // cuva izlaz komande

        std::ostream& output = (inputs.size() > 1) ? outputBuffer : std::cout;

        Command::processCommand(inputs, inputLine, prompt, output, outputBuffer);
        
    }

}
