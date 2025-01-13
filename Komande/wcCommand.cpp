#include "wcCommand.h"

#include "command.h"
#include <string>
#include <fstream>
#include <vector>
#include <ostream>

void WcCommand::execute(char &opt, std::string& argument, std::ostream& output, bool &redirectExist) {
    // provera za -opt
    if (opt != 'w' && opt != 'c') {
        output << "Error: Invalid option\n";
        return;
    }

    std::string redirectFile;
    if (redirectExist) {
        redirectFile = redirectProcess(argument);
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
        processOptW(text, output, redirectFile);
    } else if (opt == 'c') {
        processOptC(text, output, redirectFile);
    }
}

void WcCommand::processOptW(std::string& text, std::ostream& output, std::string &redirectFile) {
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
        if (!redirectFile.empty()) {
            std::ofstream file(redirectFile);
            file << countingWords(text);
        } else {
            output << countingWords(text) << '\n';
        }
    }
}

void WcCommand::processOptC(std::string& text, std::ostream& output, std::string &redirectFile) {
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
        if (!redirectFile.empty()) {
            std::ofstream file(redirectFile);
            file << text.length();
        } else {
            output << text.length() << '\n';
        }
    }
}