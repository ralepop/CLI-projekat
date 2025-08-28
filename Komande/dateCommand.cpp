#include "dateCommand.h"
#include <ctime>
#include <fstream>
#include <iomanip> // std::put_time
#include <sstream>
#include <string>

void DateCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) {
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme
    const std::tm* now = std::localtime(&t); // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima

    auto result = std::put_time(now, "%d.%m.%Y.");

    std::string redirectFile, text;

    bool doubleRedirect = false;
    if (redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    
    if (redirectExist && !redirectFile.empty()) {

        std::ofstream file(redirectFile, doubleRedirect ? std::ios::app : std::ios::out);
        file << result;

    }else if (!pipeExist || (pipeExist && isLast)) output << result << '\n';

    std::ostringstream temp;
    temp << result;
    lastResult = temp.str();
}
