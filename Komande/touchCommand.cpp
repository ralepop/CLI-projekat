#include "touchCommand.h"

#include <string>
#include <vector>

void TouchCommand::execute(char &opt, std::string &argument, std::ostream &output) {

    const std::string line = "touch " + argument;

    if (errorHandling(line)) {
        if (whitespaceExist(argument)) {

            for (std::string file : splitString(argument)) {
                createFile(file, output);
            }

        } else {
            createFile(argument, output);
        }
    }

    

}