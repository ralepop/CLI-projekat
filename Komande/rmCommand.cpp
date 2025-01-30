#include "rmCommand.h"

#include <filesystem>

void RmCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    if(newlineExist(argument)){ // ako je uneto vise linija

        std::vector<std::string> lines;
        splitNewline(argument, lines); // ubacujemo linije u vektor lines

        for(std::string &file : lines){

            if(!errorHandling(file)) continue;

            if(!std::filesystem::remove(file)) output << "Error: file " << file << " not found\n";

        }

    }else{ // ako je uneta samo jedna linija

        if(!errorHandling(argument)) return;

        if(!std::filesystem::remove(argument)) output << "Error: no file found\n";

    }

}