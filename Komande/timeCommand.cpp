#include "timeCommand.h"

void TimeCommand::execute(std::istream &input, std::ostream &output)
{
    std::time_t t {std::time(nullptr)}; // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    std::tm* now {std::localtime(&t)};

    if(now->tm_hour < 10) output << '0';
    output << now->tm_hour << ':';
    if(now->tm_min < 10) output << '0';
    output << now->tm_min << ':';
    if(now->tm_sec < 10) output << '0';
    output << now->tm_sec << '\n';

}