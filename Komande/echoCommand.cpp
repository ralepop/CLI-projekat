#include "echoCommand.h"
#include <iostream>

void EchoCommand::execute(std::istream &input, std::ostream &output)
{
    std::string line;

    bool valid = true;
    std::getline(input, line);
    char first = line[1];
    char last = line[line.length() - 1];

    if((first == '"' && last != '"') || (first != '"' && last == '"')){
        std::cerr << "Error: Invalid input\n";
        valid = false;
    }else if(!line.empty() && first == '"' && last == '"'){
        line = line.substr(2, line.size() - 3);
    }

    if(valid) output << line << std::endl;

    
}