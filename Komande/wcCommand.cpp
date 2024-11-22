#include "wcCommand.h"

void WcCommand::execute(std::istream &input, std::ostream &output)
{
    // TODO: ubaci f-ju checkLine

    std::string opt {};

    input >> opt;

    if(opt != "-w" && opt != "-c"){
        output << "Error: Invalid -opt\n";
    }else{

        std::string line {};
        bool rec {false};
        int i {0};

        std::getline(input, line);

        bool valid {checkLine(line)};

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
        }else{
            output << "Error: Invalid input\n";
        }
    }

}