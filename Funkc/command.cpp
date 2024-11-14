#include "command.h"

bool Command::checkLine(std::string &line)
{
    char first = line[1];
    char last = line[line.length() - 1];

    if((first == '"' && last != '"') || (first != '"' && last == '"')){
        std::cerr << "Error: Invalid input\n";
        return false;
    }else if(!line.empty() && first == '"' && last == '"'){
        line = line.substr(2, line.size() - 3);
        return true;
    }else{
        line = line.substr(1, line.size());
        return true;
    }
}