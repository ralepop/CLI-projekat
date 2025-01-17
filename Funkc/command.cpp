#include "command.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>


bool Command::newlineExist(const std::string &line) {
    return (line.find('\n') != std::string::npos);
}

void Command::splitNewline(const std::string &line, std::vector<std::string> &lines) {
    size_t start = 0;
    size_t end = line.find('\n');

    while (end != std::string::npos) {
        lines.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find('\n', start); // nalazimo sledeci '\n'
    }
    lines.push_back(line.substr(start, line.length() - start));
}


bool Command::checkLine(std::string &line) {

    if (line.empty()) return false;

    const size_t firstQuo = line.find_first_of('"');
    const size_t lastQuo = line.find_last_of('"');

    // ukoliko nema dva navodnika
    if (firstQuo == std::string::npos || lastQuo == std::string::npos || firstQuo == lastQuo) {

        for (const char ch : line) {
            if (ch == ' ') return false;
        }
        return true;
    }

    // proverava da li ima nesto pre ili posle navodnika
    if (firstQuo != 0 || lastQuo != line.size() - 1) return false;

    const std::string argument = line.substr(firstQuo + 1, lastQuo - firstQuo - 1);
    if (argument.empty()) return false;
    line = argument;

    return true;

}

void Command::stripQuo(std::string &line) {
    if(line.size() >= 2) {
        line = line.substr(1, line.size() - 2);
    }
}

bool Command::checkIfFile(std::string &line, const std::string& filetype) {
    if (line.size() < filetype.size() + 1) return false;

    const size_t pos = line.find('<'); // trazimo poziciju ulaznog znakovnog toka
    if (pos != std::string::npos) { // proveravamo da li ulazni znakovni tok uopste postoji
        line = line.substr(pos + 1, line.length()); // skidamo znak '<'
        stripWhitespace(line);
    }
    return line.ends_with('.' + filetype);
}

std::string Command::putIntoString(const std::string& line) {
    std::ifstream file(line);

    if (!file.is_open()) {
        std::cout << "Error: no file found\n";
        return "";
    }

    std::string text;
    std::string temp;

    while(std::getline(file, temp)){
        text += temp + '\n';
    }

    return text;
}

void Command::stripWhitespace(std::string &line) {

    if (line.empty()) return;

    const char* whiteSpace = " \t\n";

    const std::size_t left = line.find_first_not_of(whiteSpace); // prvi karakter koji nije whitespace
    const std::size_t right = line.find_last_not_of(whiteSpace); // poslednji karakter koji nije whitespace

    if (left == right) line = line.substr(left, 1);
    else line = line.substr(left, right - left + 1);
   
}

std::vector<std::string> Command::splitString(const std::string &line, char c) {
    std::vector<std::string> result;
    std::string temp;
    size_t start = 0;
    size_t end = 0;

    while ( (end = line.find(c, start)) != std::string::npos ) {
        temp = line.substr(start, end - start);
        stripWhitespace(temp);

        result.push_back(temp);
        start = end + 1;
    }

    // za poslednju
    // ako je recimo unos: cmd1 | cmd2 | cmd3 temp uzima cmd3
    temp = line.substr(start);
    stripWhitespace(temp);
    result.push_back(temp);

    return result;
}

void Command::createFile(std::string &filename, std::ostream &output) {
    std::ifstream infile(filename);

    if(infile.is_open()) {
        output << "Error: File " << filename << " already exists.\n";
        return;
    }


    std::ofstream file(filename);

    if (!file) {
        output << "Error: Could not create the file " << filename << ".\n";
    }

}

std::string Command::commandName(std::string &line) {

    std::size_t pos = line.find_first_of(" ");

    if (pos != std::string::npos) {
        std::string command = line.substr(0, pos);
        line = line.substr(pos + 1);
        return command;
    }

    std::string command = line;
    line.clear();
    return command;
}

char Command::opt(std::string &line) {
    
    std::size_t pos = line.find('-');

    // proveravamo da li je pretraga uspesna i da li postoji barem jedan karakter nakon pos
    if (pos != std::string::npos && pos + 1 < line.size()) {
        const char opt = line[pos + 1];
        line = line.substr(pos + 2);
        return opt;
    }
    return '\0';
}

bool Command::whitespaceExist(const std::string &line) {
    for (const char c : line) {
        if (std::isspace(c)) return true;
    }

    return false;
}

bool Command::redirectExist(const std::string &line) {
    return line.find('>') != std::string::npos;
}

std::string Command::redirectProcess(std::string &line, bool &doubleRedirect) {

    const size_t posTxt = line.find(".txt");

    if (posTxt != std::string::npos) {
        size_t pos = line.rfind(">>", posTxt);

        if (pos != std::string::npos) {
            std::string redirectFile = line.substr(pos + 2, posTxt - pos + 4);
            doubleRedirect = true;
            line = line.substr(0, pos);
            stripWhitespace(line);
            stripWhitespace(redirectFile);
            return redirectFile;
        }

        pos = line.rfind('>', posTxt);
        if (pos != std::string::npos) {
            std::string redirectFile = line.substr(pos + 1, posTxt - pos + 4);
            line = line.substr(0, pos);
            stripWhitespace(line);
            stripWhitespace(redirectFile);
            return redirectFile;
        }
    }
    return "";
}

bool Command::pipeExist(const std::string &line) {
    return line.find('|') != std::string::npos;
}

bool Command::errorHandling(const std::string &line) {
    const std::string validSymbols = "-\"<>.|: ";
    bool fine = true;

    std::vector<size_t> errorPositions;

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];

        if (!std::isalnum(c) && validSymbols.find(c) == std::string::npos) {
            errorPositions.push_back(i);
        }
    }

    if (!errorPositions.empty()) {
        std::cout << "Error - unexpected characters:\n";
        std::cout << line << '\n';
        fine = false;

        for (size_t i = 0; i < line.length(); ++i) {
            std::cout << (std::find(errorPositions.begin(), errorPositions.end(), i) != errorPositions.end() ? '^' : ' ');
        }
        std::cout << '\n';
    }
    return fine;

}
