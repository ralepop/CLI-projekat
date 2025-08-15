#include "dateCommand.h"
#include <ctime>
#include <fstream>
#include <iomanip> // std::put_time

void DateCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) {
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme
    const std::tm* now = std::localtime(&t); // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima

    if (redirectExist) {
        std::string redirectFile = redirectProcess(argument, redirectExist);
        std::string text = putIntoString(redirectFile);
        if (!redirectFile.empty()) {
            std::ofstream file(redirectFile, std::ios_base::app);
            file << "\n" << std::put_time(now, "%d.%m.%Y.") << "\n";
        } // TODO: SREDI NOVE REDOVE
        output << text << std::endl;
    }
    output << std::put_time(now, "%d.%m.%Y.") << "\n";
}
