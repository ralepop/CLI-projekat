#include "echoCommand.h"
#include "command.h"
#include <iostream>
#include <string>

void EchoCommand::execute(std::string &argument, std::ostream &output)
{
    std::string text {};

    // std::getline(input, line);

    stripWhitespace(argument);
    bool isFile {checkIfFile(argument, "txt")};
    const bool valid {checkLine(argument)};
    
    std::string fullPath {defaultPath + argument};

    if(isFile && valid){
        text = putIntoString(fullPath);
    }else if(valid){
        text = argument;
    }

    if(valid) output << text << std::endl;
    else output << "Error: Invalid input\n";

}