#include "timeCommand.h"
#include <ctime>
#include <fstream>
#include <iomanip> // setfill, setw
#include <sstream>

void TimeCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){
    
    const std::time_t t = std::time(nullptr); // vraca trenutno vreme

    // std::tm* je pokazivac na strukturu koja sadrzi info o satima, minutima...
    // now sadrzi lokalno vreme
    const std::tm* now = std::localtime(&t);
    
    std::ostringstream temp;
    temp
        << std::setfill('0')
        << std::setw(2) << now->tm_hour << ':'
        << std::setw(2) << now->tm_min << ':'
        << std::setw(2) << now->tm_sec << '\n';
    std::string result = temp.str(), redirectFile, text;

    bool doubleRedirect = false;
    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    if(redirectExist && !redirectFile.empty()){
        std::ofstream file(redirectFile, std::ios::out);
        file << result;

        text = putIntoString(redirectFile);
        output << text;
        file.close();
    }else if(!pipeExist || (pipeExist && isLast)){
        output << result;
    }
    lastResult = result;
}