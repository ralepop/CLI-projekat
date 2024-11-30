#include "wcCommand.h"
#include <string>

void WcCommand::execute(std::istream &input, std::ostream &output)
{
    
    std::string opt {};
    input >> opt;

    if(opt != "-w" && opt != "-c"){
        output << "Error: Invalid -opt\n";
    }else{

        std::string line {};
        std::string text {};
        std::getline(input, line);
        stripWhitespace(line);
        bool isFile {checkIfFile(line, "txt")};
        bool valid {checkLine(line)};

        std::string fullPath {defaultPath + line};

        if(isFile && valid){
            text = putIntoString(fullPath);

        }else if(valid){
            text = line;

        }

        bool word {false};
        int i {0};

        if(valid){
            for(char c : text){
                if(opt == "-w"){
                    if(std::isspace(c)) word = false;
                    else if(!word){
                        i++;
                        word = true;
                    }
                }else if(opt == "-c") i++;
            }

            output << i << std::endl;

        }else output << "Error: Invalid input\n";
    }

}