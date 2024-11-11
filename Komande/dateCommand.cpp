#include "dateCommand.h"

void DateCommand::execute(std::istream &input, std::ostream &output)
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    output << now->tm_mday << '/' << now->tm_mon << '/' << now->tm_year << '\n';
}