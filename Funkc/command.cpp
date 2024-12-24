#include "command.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include <fstream>


bool Command::checkLine(std::string &line) {
    stripWhitespace(line);

    if (line.empty()) return false;

    const size_t firstQuo = line.find_first_of('"');
    const size_t lastQuo = line.find_last_of('"');

    // ukoliko nema dva navodnika
    if (firstQuo == std::string::npos || lastQuo == std::string::npos || firstQuo == lastQuo) {

        for (const char ch : line) {
            if (std::isspace(ch)) return false;
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

bool Command::checkIfFile(const std::string &line, const std::string& filetype) {
    if (line.size() < filetype.size() + 1) return false;
    return line.ends_with(filetype) && line[line.size() - filetype.size() - 1] == '.';
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
     
    const char* whiteSpace = " \t\n";

    const std::size_t left = line.find_first_not_of(whiteSpace); // prvi karakter koji nije whitespace
    const std::size_t right = line.find_last_not_of(whiteSpace); // poslednji karakter koji nije whitespace

    if (left == right) line.clear();
    else line = line.substr(left, right - left + 1);
   
}

std::vector<std::string> Command::splitString(const std::string &line) {
    std::vector<std::string> words;

    bool isQuo = false;
    size_t quoPosition = 0;
    char c;
    size_t front = 0;


    for (size_t i = 0; i <= line.size(); ++i) {
        c = line[i];
        if (c == '\"' && !isQuo) {
            quoPosition = i;
            isQuo = true;
        } else if (c == '\"') {
            words.push_back(line.substr(quoPosition + 1, i - quoPosition - 1));
            isQuo = false;
            i++;
            front = i + 1;
        }


        if (i == line.size() || c == ' ' && !isQuo) {
            words.push_back(line.substr(front, i - front));
            front = i + 1;
        }
    }

    return words;
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

bool Command::whitespaceExist(std::string &line) {
    for (const char c : line) {
        if (std::isspace(c)) return true;
    }

    return false;
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
