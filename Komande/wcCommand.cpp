#include "wcCommand.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include <ostream>

void WcCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){
    
    // provera za -opt
    if(opt != "-w" && opt != "-c"){
        output << "Error: Invalid option\n";
        return;
    }

    std::string redirectFile, text;
    bool doubleRedirect = false, valid = true;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    // pamtimo unos u string text
    const bool isFile = checkIfFile(argument, "txt");

    if(isFile){
        text = putIntoString(argument);
        if(text.empty()) return;
    }else if(pipeExist && !lastResult.empty()) text = lastResult;
    else text = argument;

    if(!newlineExist(text) && !pipeExist && !isFile) valid = checkLine(text);

    if(!valid){
        const std::string errorLine = "wc " + opt + " " + argument;
        if(!isFile && errorHandling(errorLine)) output << "Error: Invalid input\n";
        return;
    }

    // procesuiramo za odredjeni -opt
    if(opt == "-w") processOptW(text, output, redirectFile, doubleRedirect, lastResult, pipeExist, isFirst, isLast);
    else if(opt == "-c") processOptC(text, output, redirectFile, doubleRedirect, lastResult, pipeExist, isFirst, isLast);
}

void WcCommand::processOptW(std::string& text, std::ostream& output, std::string &redirectFile, bool &doubleRedirect, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){
    size_t i = 0;

    if(newlineExist(text)){
        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);

        for(std::string& line : lines){
            i += countingWords(line);
        }
    }

    size_t result = newlineExist(text) ? i : countingWords(text);

    if(!redirectFile.empty()){
        std::ofstream file(redirectFile, doubleRedirect ? std::ios::app : std::ios::out);
        if(doubleRedirect) file << '\n';
        file << result;
        file.close();
    }else if(!pipeExist || (pipeExist && isLast)){
        output << result << '\n';
    }
    lastResult = std::to_string(result);
}

void WcCommand::processOptC(std::string& text, std::ostream& output, std::string &redirectFile, bool &doubleRedirect, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){
    size_t i = 0;
    
    if(newlineExist(text)){
        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);

        for(std::string& line : lines){
            i += line.length();
        }
    }

    size_t result = newlineExist(text) ? i : text.length();

    if(!redirectFile.empty()){
        std::ofstream file(redirectFile, doubleRedirect ? std::ios::app : std::ios::out);
        if(doubleRedirect) file << '\n';
        file << result;
        file.close();
    }else if(!pipeExist || (pipeExist && isLast)){
        output << result << '\n';
    }
    lastResult = std::to_string(result);
}