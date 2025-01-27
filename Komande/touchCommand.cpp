#include "touchCommand.h"

#include <string>
#include <vector>

void TouchCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult){


    if(newlineExist(argument)){ // ako je uneto vise linija

        std::vector<std::string> lines;
        splitNewline(argument, lines); // ubacujemo linije u vektor lines

        for(std::string &file : lines){
            if(errorHandling(file)){
                createFile(file, output);
            }
        }

    }else{ // ako je uneta samo jedna linija
        if(errorHandling(argument)){
            createFile(argument, output);
        }

    }
    

}