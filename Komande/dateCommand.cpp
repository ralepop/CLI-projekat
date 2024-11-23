#include "dateCommand.h"

void DateCommand::execute(std::istream &input, std::ostream &output)
{
    std::time_t t {std::time(0)}; // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    std::tm* now {std::localtime(&t)};

    output << now->tm_mday << '/' << now->tm_mon + 1 << '/' << now->tm_year + 1900 << '\n';
}