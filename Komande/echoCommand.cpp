#include "echoCommand.h"
#include "command.h"
#include <iostream>
#include <string>

void EchoCommand::execute(char &opt, std::string &argument, std::ostream &output) {
    
    std::string text;

    stripWhitespace(argument);
    const bool isFile = checkIfFile(argument, "txt");
    const bool valid = checkLine(argument);

    const std::string fullPath = defaultPath + argument;

    if (isFile && valid) {
        text = putIntoString(fullPath);
    } else if (valid) {
        text = argument;
    }

    if (valid) {
        if(isFile) output << text;
        else output << text << std::endl;
    }
    else {
        output << "Error: Invalid input\n";
    }

}