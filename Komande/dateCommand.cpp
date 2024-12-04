#include "dateCommand.h"
#include <ctime>

void DateCommand::execute(std::string &argument, std::ostream &output)
{  

    std::time_t t {std::time(nullptr)}; // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    std::tm* now {std::localtime(&t)};

    output << now->tm_mday << '/' << now->tm_mon + 1 << '/' << now->tm_year + 1900 << '\n';
}