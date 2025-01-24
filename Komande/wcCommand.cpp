#include "wcCommand.h"

#include <string>
#include <fstream>
#include <vector>
#include <ostream>

void WcCommand::execute(char &opt, std::string& argument, std::ostream& output, bool &redirectExist, std::string &lastResult){
    // provera za -opt
    if(opt != 'w' && opt != 'c'){
        output << "Error: Invalid option\n";
        return;
    }

    std::string redirectFile;
    bool doubleRedirect = false;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    bool pipeExist = !lastResult.empty() ? true : false;

    // pamtimo unos u string text
    std::string text;

    bool isFile = checkIfFile(argument, "txt");
    if(isFile && !redirectExist){
        text = putIntoString(argument);
        if(text.empty()) return;
    } else if(!pipeExist) text = argument;
    else text = lastResult;

    // proveravamo valinost
    bool valid = true;
    if(!newlineExist(text) && !pipeExist) valid = checkLine(text);

    if(!valid){
        std::string errorLine = "wc " + std::string(1, opt) + " " + argument;
        if(!isFile && errorHandling(errorLine)) output << "Error: Invalid input\n";
        return;
    }

    // procesuiramo za odredjeni -opt
    if(opt == 'w') processOptW(text, output, redirectFile, doubleRedirect, lastResult);
    else if(opt == 'c') processOptC(text, output, redirectFile, doubleRedirect, lastResult);
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

    } else {
        // kada je uneta jedna linija
        if(!redirectFile.empty()){
            if(doubleRedirect){
                std::ofstream file(redirectFile, std::ios::app); // otvaramo u modu dodavanja
                file << '\n' << countingWords(text);
                file.close();
            } else {
                std::ofstream file(redirectFile, std::ios::out); // otvaramo u modu skroz novog fajla
                file << countingWords(text);
                file.close();
            }
        } else {
            output << countingWords(text) << '\n';
        }
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

    } else {
        // kada je uneta jedna linija
        if(!redirectFile.empty()){
            if(doubleRedirect){
                std::ofstream file(redirectFile, std::ios::app); // otvaramo u modu dodavanja
                file << '\n' << text.length();
                file.close();
            } else {
                std::ofstream file(redirectFile, std::ios::out); // otvaramo u modu skroz novog fajla
                file << text.length();
                file.close();
            }
        } else {
            output << text.length() << '\n';
        }
    }
}