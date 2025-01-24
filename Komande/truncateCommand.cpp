#include "truncateCommand.h"

#include "command.h"
#include <fstream>

void TruncateCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){

    if(newlineExist(argument)){ // ako je uneto vise linija

        std::vector<std::string> lines;
        splitNewline(argument, lines); // ubacujemo linije u vektor lines

        for(std::string &line : lines){

            if(!errorHandling(line)){
                continue;
            }

            std::ofstream file(line, std::ios::trunc);
            if(!file){
                output << "Error: file " << line << " not found\n";
            }
        }

    }else{ // ako je uneta samo jedna linija

        if(!errorHandling(argument)){
            return;
        }

        std::ofstream file(argument, std::ios::trunc);
        if(!file){
            output << "Error: no file found\n";
        }

    }
}