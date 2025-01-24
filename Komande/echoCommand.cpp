#include "echoCommand.h"

#include "command.h"
#include <fstream>
#include <string>
#include <vector>

void EchoCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    std::string redirectFile;

    bool doubleRedirect = false;
    if(redirectExist){
        redirectFile = redirectProcess(argument, doubleRedirect); // procesuiramo argument ako ima redirect znak
    }

    const bool isFile = checkIfFile(argument, "txt");
    bool valid = true;

    std::string text;
    if(isFile){
        text = putIntoString(argument);
    }else{
        text = argument;
    }

    if(!newlineExist(text)){
        valid = checkLine(text); // proverava ako je uneta jedna linija
    }

    if(valid){
        if(newlineExist(text)){ // ako je uneto vise linija
            std::vector<std::string> lines;
            splitNewline(text, lines); // ubacujemo linije u vektor lines

            for(std::string &line : lines){
                output << line << std::endl;
            }

        }else{ // ako je uneta samo jedna linija

            if(redirectExist && !redirectFile.empty()){ // u fajl jer postoji redirect znak
                std::ofstream file(redirectFile, std::ios::out);
                file << text;
                file.close();
            }else{
                output << text << std::endl;
            }
        }

    }else{
        const std::string line = "echo " + argument;
        if(errorHandling(line)){
            output << "Error: Invalid input\n";
        }
    }
}