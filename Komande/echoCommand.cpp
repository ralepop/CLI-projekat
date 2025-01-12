#include "echoCommand.h"
#include "command.h"
#include <iostream>
#include <string>
#include <vector>

void EchoCommand::execute(char &opt, std::string &argument, std::ostream &output) {
    std::string text;

    const bool isFile = checkIfFile(argument, "txt");
    bool valid = true;

    if (isFile) {
        text = putIntoString(argument);
    } else {
        text = argument;
    }

    if (!newlineExist(text)) {
        valid = checkLine(text); // proverava ako je uneta jedna linija
    }

    if (valid) {
        if (newlineExist(text)) { // ako je uneto vise linija
            std::vector<std::string> lines;
            splitNewline(text, lines); // ubacujemo linije u vektor lines

            for (std::string &line : lines) {
                output << line << std::endl;
            }
        } else {
            output << text << std::endl; // ako je uneta samo jedna linija
        }
    } else {
        const std::string line = "echo " + argument;
        if (errorHandling(line)) {
            output << "Error: Invalid input\n";
        }
    }
}