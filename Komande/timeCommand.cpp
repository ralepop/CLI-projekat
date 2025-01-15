#include "timeCommand.h"
#include <ctime>
#include <fstream>
#include <iomanip> // setfill, setw

void TimeCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) {
    
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    const std::tm* now = std::localtime(&t);

    std::string redirectFile;
    bool doubleRedirect = false;
    if (redirectExist) {
        redirectFile = redirectProcess(argument, doubleRedirect);
    }

    if (redirectExist && !redirectFile.empty()) {
        std::ofstream file(redirectFile);
        file
            << std::setfill('0')
            << std::setw(2) << now->tm_hour << ':'
            << std::setw(2) << now->tm_min << ':'
            << std::setw(2) << now->tm_sec << '\n';
    } else {
        output
            << std::setfill('0')
            << std::setw(2) << now->tm_hour << ':'
            << std::setw(2) << now->tm_min << ':'
            << std::setw(2) << now->tm_sec << '\n';
    }
}