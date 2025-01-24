#include "trCommand.h"

#include "command.h"
#include <sstream>
#include <string>

void TrCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    // output = "todor petkovic"
    // input = tr "ted" with "rale"
    // argument = "ted" with "rale"
    // rezultat = "rolor parkovic"

    // uzimamo iz outputa da bismo uzeli poslednji output
    std::string mainStr = dynamic_cast<std::ostringstream&>(output).str();

    size_t firstQuo = argument.find('\"'); // 0
    size_t secondQuo = argument.find('\"', firstQuo + 1); // 5
    size_t fourthQuo = argument.rfind('\"'); // 18
    size_t thirdQuo = argument.rfind('\"', fourthQuo - 1); // 12

    std::string with = argument.substr(thirdQuo + 1, fourthQuo - thirdQuo - 1); // rale
    argument = argument.substr(firstQuo + 1, secondQuo - firstQuo - 1); // ted


    for(size_t i = 0; i < mainStr.length(); ++i){
        size_t pos = argument.find(mainStr[i]);
        if(pos != std::string::npos){
            mainStr[i] = with[pos >= with.length() ? with.length() - 1 : pos];
        }
    }



    output << mainStr;



}