#include "timeCommand.h"

void TimeCommand::execute(std::istream &input, std::ostream &output)
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    output << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << '\n';
}