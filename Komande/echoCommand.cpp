#include "echoCommand.h"
#include <iostream>
#include <string>

void EchoCommand::execute(std::istream &input, std::ostream &output)
{
    std::string line {};

    std::getline(input, line);
    const bool valid {checkLine(line)};
    
    if(valid) output << line << std::endl;
    else output << "Error: Invalid input\n";
    
}