#include "echoCommand.h"
#include "command.h"
#include <iostream>
#include <string>

void EchoCommand::execute(char &opt, std::string &argument, std::ostream &output) {
    
    std::string text;

    const bool isFile = checkIfFile(argument, "txt");
    const bool valid = checkLine(argument);

    if (isFile && valid) {
        text = putIntoString(argument);
    } else if (valid) {
        text = argument;
    }

    if (valid) {
        if(isFile) output << text;
        else output << text << std::endl;
    } else {

        const std::string line = "echo " + argument;
        if (errorHandling(line)) {
           output << "Error: Invalid input\n";
        }

    }

}