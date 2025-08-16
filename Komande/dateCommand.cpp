#include "dateCommand.h"
#include <ctime>
#include <fstream>
#include <iomanip> // std::put_time
#include <sstream>
#include <string>

void DateCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast) {
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme
    const std::tm* now = std::localtime(&t); // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima

    auto result = std::put_time(now, "%d.%m.%Y.\n");

    std::string redirectFile, text;
    if(redirectExist) redirectFile = redirectProcess(argument, redirectExist);

    
    if (redirectExist && !redirectFile.empty()) {
        std::ofstream file(redirectFile, std::ios::out);
        file << result;

        text = putIntoString(redirectFile);
        output << text;
        file.close();
    }else if(!pipeExist || (pipeExist && isLast)){
        output << result;
    }
    std::ostringstream temp;
    temp << result;
    lastResult = temp.str();
}
