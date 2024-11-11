#include "echoCommand.h"

void EchoCommand::execute(std::istream &input, std::ostream &output)
{
    std::string line;
    std::getline(input, line);
    output << line << std::endl;
}