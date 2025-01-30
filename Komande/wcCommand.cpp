#include "wcCommand.h"

#include <string>
#include <fstream>
#include <vector>
#include <ostream>

void WcCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){
    
    // provera za -opt
    if(opt != "-w" && opt != "-c"){
        output << "Error: Invalid option\n";
        return;
    }

    std::string redirectFile, text;
    bool doubleRedirect = false, valid = true, pipeExist = !lastResult.empty() ? true : false;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    // pamtimo unos u string text
    const bool isFile = checkIfFile(argument, "txt");

    if(isFile && !redirectExist){
        text = putIntoString(argument);
        if(text.empty()) return;
    }else if(!pipeExist) text = argument;
    else text = lastResult;

    if(!newlineExist(text) && !pipeExist && !isFile) valid = checkLine(text);

    if(!valid){
        const std::string errorLine = "wc " + opt + " " + argument;
        if(!isFile && errorHandling(errorLine)) output << "Error: Invalid input\n";
        return;
    }

    // procesuiramo za odredjeni -opt
    if(opt == "-w") processOptW(text, output, redirectFile, doubleRedirect, lastResult);
    else if(opt == "-c") processOptC(text, output, redirectFile, doubleRedirect, lastResult);
}

void WcCommand::processOptW(std::string& text, std::ostream& output, std::string &redirectFile, bool &doubleRedirect, std::string &lastResult){
    if(newlineExist(text)){

        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);
        size_t i = 0;

        for(std::string& line : lines){
            i += countingWords(line);
        }
        output << i << '\n';

    }else{
        // kada je uneta jedna linija
        if(!redirectFile.empty()){

            std::ofstream file(redirectFile, doubleRedirect ? std::ios::app : std::ios::out);
            if(doubleRedirect) file << '\n';
            file << text.length();
            file.close();

        }else output << countingWords(text) << '\n';
    }
}

void WcCommand::processOptC(std::string& text, std::ostream& output, std::string &redirectFile, bool &doubleRedirect, std::string &lastResult){
    
    if(newlineExist(text)){
        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);
        size_t i = 0;

        for(std::string& line : lines){
            i += line.length();
        }
        output << i << '\n';

    }else{
        // kada je uneta jedna linija
        if(!redirectFile.empty()){

            std::ofstream file(redirectFile, doubleRedirect ? std::ios::app : std::ios::out);
            if(doubleRedirect) file << '\n';
            file << text.length();
            file.close();

        }else output << text.length() << '\n';
    }
}