#include "wcCommand.h"

#include "command.h"
#include <string>

void WcCommand::execute(char &opt, std::string &argument, std::ostream &output)
{

    if(opt != 'w' && opt != 'c'){
        output << "Error: Invalid -opt\n";
    }else{

        std::string text {};
        stripWhitespace(argument);
        const bool isFile (checkIfFile(argument, "txt"));
        const bool valid (checkLine(argument));


        if(isFile && valid){
            text = putIntoString(argument);
        }else if(valid){
            text = argument;
        }

        bool word {false};
        int i {0};

        if (valid) {
            if(opt == 'w'){
                for(const char c : text){
                    if(std::isspace(c)) word = false;
                    else if(!word){
                        i++;
                        word = true;
                    }
                }
            } else {
                i = text.length();
            }

            output << i << std::endl;

        } else {



            const std::string line = "wc " + std::string{opt} + " " + argument;
            if (errorHandling(line)) {
                output << "Error: Invalid input\n";
            }

        }
    }


}