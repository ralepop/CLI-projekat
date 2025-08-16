#include "echoCommand.h"

#include <fstream>
#include <string>
#include <vector>

void EchoCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){

    std::string redirectFile, text;
    bool doubleRedirect = false, valid = true;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    const bool isFile = checkIfFile(argument, "txt");

    if(isFile){
        text = putIntoString(argument);
        if(text.empty()) return;
    }else if(pipeExist && !lastResult.empty()) text = lastResult;
    else text = argument;

    if(!newlineExist(text) && !pipeExist && !isFile) valid = checkLine(text);

    if(!valid){
        // TODO: proveri da li ovde stavljati argument ili text
        const std::string errorLine = "echo " + opt + " " + argument;
        if(!isFile && errorHandling(errorLine)) output << "Error: Invalid input\n";
        return;
    }

    if(newlineExist(text) && !redirectExist){
        std::vector<std::string> lines;
        splitNewline(text, lines); // ubacujemo linije u vektor lines

        for(std::string &line : lines){
            output << line << std::endl;
        }
    }else{ // ako je uneta samo jedna linija
        if(redirectExist && !redirectFile.empty()){ // u fajl jer postoji redirect znak
            std::ofstream file(redirectFile, std::ios::out);
            file << text;
            output << text;
            if(doubleRedirect){
                output << text << std::endl;
                file << text;
            }else output << std::endl;
            file.close();
        }else if(!pipeExist || (pipeExist && isLast)){
            output << text << std::endl;
        }
    }
    lastResult = text;
}