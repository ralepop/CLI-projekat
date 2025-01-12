#include "wcCommand.h"
#include "command.h"
#include <string>
#include <vector>
#include <ostream>

void WcCommand::execute(char &opt, std::string& argument, std::ostream& output) {
    // provera za -opt
    if (opt != 'w' && opt != 'c') {
        output << "Error: Invalid option\n";
        return;
    }

    // pamtimo unos
    std::string text;
    bool isFile = checkIfFile(argument, "txt");
    if (isFile) {
        text = putIntoString(argument);
    } else {
        text = argument;
    }

    // proveravamo valinost
    bool valid = true;
    if (!newlineExist(text)) {
        valid = checkLine(text);
    }

    if (!valid) {
        std::string errorLine = "wc " + std::string(1, opt) + " " + argument;
        if (errorHandling(errorLine)) {
            output << "Error: Invalid input\n";
        }
        return;
    }

    // procesuiramo za odredjeni -opt
    if (opt == 'w') {
        processOptW(text, output);
    } else if (opt == 'c') {
        processOptC(text, output);
    }
}

void WcCommand::processOptW(const std::string& text, std::ostream& output) {
    if (newlineExist(text)) {
        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);
        size_t i = 0;

        for (std::string& line : lines) {
            i += countingWords(line);
        }
        output << i << '\n';

    } else {
        // kada je uneta jedna linija
        output << countingWords(text) << '\n';
    }
}

void WcCommand::processOptC(const std::string& text, std::ostream& output) {
    if (newlineExist(text)) {
        // delimo linije i procesuiramo svako
        std::vector<std::string> lines;
        splitNewline(text, lines);
        size_t i = 0;

        for (std::string& line : lines) {
            i += line.length();
        }
        output << i << '\n';

    } else {
        // kada je uneta jedna linija
        output << text.length() << '\n';
    }
}