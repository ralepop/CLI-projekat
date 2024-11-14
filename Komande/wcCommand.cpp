#include "wcCommand.h"

void WcCommand::execute(std::istream &input, std::ostream &output)
{
    // TODO: ubaci f-ju checkLine

    std::string opt {};

    input >> opt;

    if(opt != "-w" && opt != "-c"){
        std::cerr << "Error: Invalid -opt\n";
    }else{

        std::string line {};
        bool valid {true}, rec {false};
        int i {0};

        std::getline(input, line);

        char first {line[1]};
        char last {line[line.length() - 1]};

        if((first == '"' && last != '"') || (first != '"' && last == '"')){
            std::cerr << "Error: Invalid input\n";
            valid = false;
        }else if(!line.empty() && first == '"' && last == '"'){
            line = line.substr(2, line.size() - 3);
        }else{
            line = line.substr(1, line.size());
        }
        if(valid){
            for(char c : line){
                if(opt == "-w"){
                    if(std::isspace(c)){
                        rec = false;
                    }else{
                        if(!rec){
                            i++;
                            rec = true;
                        }
                    }
                }else if(opt == "-c"){
                    if(!std::isspace(c)) i++;
                }
            }
            output << i << std::endl;
        }
    }

}