#include "trCommand.h"

#include <sstream>
#include <string>

void TrCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    // uzimamo iz outputa da bismo uzeli poslednji output
    // std::string mainStr = dynamic_cast<std::ostringstream&>(output).str();
    // FIXME: namestiti da moze da uzima 3 stringa ukoliko nije dat mainStr (last input). ukoliko je on dat sve radi lepo
    size_t firstQuo = argument.find('\"');
    size_t secondQuo = argument.find('\"', firstQuo + 1);
    size_t fourthQuo = argument.rfind('\"');
    size_t thirdQuo = argument.rfind('\"', fourthQuo - 1);

    std::string with = argument.substr(thirdQuo + 1, fourthQuo - thirdQuo - 1);
    argument = argument.substr(firstQuo + 1, secondQuo - firstQuo - 1);

    for(size_t i = 0; i < lastResult.length(); ++i){
        size_t pos = argument.find(lastResult[i]);
        if(pos != std::string::npos) lastResult[i] = with[pos >= with.length() ? with.length() - 1 : pos];
        
    }

    output << lastResult; // FIXME: moramo specifirati da je output u consoli ili fajl ili sta god
}