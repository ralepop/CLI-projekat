#include "wcCommand.h"

#include "command.h"
#include <string>

void WcCommand::execute(std::string &argument, std::ostream &output)
{
    std::string opt {argument.substr(0, 2)};
    argument = argument.substr(3);


    if(opt != "-w" && opt != "-c"){
        output << "Error: Invalid -opt\n";
    }else{

        std::string line {};
        std::string text {};
        stripWhitespace(argument);
        const bool isFile {checkIfFile(argument, "txt")};
        const bool valid {checkLine(argument)};

        const std::string fullPath {defaultPath + argument};

        if(isFile && valid){
            text = putIntoString(fullPath);
        }else if(valid){
            text = argument;
        }

        bool word {false};
        int i {0};

        if(valid){
            if(opt == "-w"){
                for(const char c : text){
                    if(std::isspace(c)) word = false;
                    else if(!word){
                        i++;
                        word = true;
                    }
                }
            }else if(opt == "-c"){
                i = text.length();
            }

            output << i << std::endl;

        }else output << "Error: Invalid input\n";
    }


}