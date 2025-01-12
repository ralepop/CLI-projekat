#include "dateCommand.h"
#include <ctime>
#include <iomanip> // std::put_time

void DateCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) {
    
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    const std::tm* now = std::localtime(&t);

    output << std::put_time(now, "%d.%m.%Y") << ".\n";
}