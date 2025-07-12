#include "headCommand.h"

#include <ostream>
#include <cctype>
#include <string>
#include <algorithm>


void HeadCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    // proveravamo da li opt pocinje sa -n
    if(opt.rfind("-n", 0) != 0){
        output << "Error: Invalid -ncount.\n";
        return;
    }

    std::string redirectFile, text;
    bool doubleRedirect = false, valid = true, pipeExist = !lastResult.empty() ? true : false, wasNewline = false;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    const bool isFile  = checkIfFile(argument, "txt");

    if(isFile){
        text = putIntoString(argument);
        if(text.empty()) return;
    }else if(!pipeExist) text = argument;
    else text = lastResult;

    if(!newlineExist(text) && !pipeExist && !isFile) valid = checkLine(text);

    if(!valid){
        const std::string errorLine = "head " + opt + " " + argument;
        if(!isFile && errorHandling(errorLine)) output << "Error: Invalid input\n";
        return;
    }

    opt = opt.substr(2); // uzimamo deo nakon "-n"

    if(opt.empty() || opt.length() > 5 || !std::all_of(opt.begin(), opt.end(), ::isdigit)) output << "Error: Invalid input.\n";

    int num = std::stoi(opt), j = 0;

    for(size_t i = 0; i < text.size(); ++i){

        if(text[i] == '\n'){
            wasNewline = true;
            output << '\n';
            j++;
            if(j == num) break;
        }else wasNewline = false;

        if(!wasNewline) output << text[i];
    }
}