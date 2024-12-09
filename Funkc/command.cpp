#include "command.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <algorithm>
#include <fstream>

bool Command::checkLine(std::string &line) {

    stripWhitespace(line);

    if (line.empty()) return false;

    char first = line.front();
    char last = line.back();
    bool spaceUsed = false;
    bool quotationUsed = false;
    int numOfQuotationsUsed = 0;

    // proveravamo da li ima space
    for(char c : line){
        if (std::isspace(c)) {
            spaceUsed = true;
        } else if (c == '"') {
            quotationUsed = true;
            ++numOfQuotationsUsed;
        }
    }

    // ako je uneta samo jedna rec
    if(!spaceUsed && !quotationUsed) return true;

    // ako je uneta samo jedna rec i " znak, npr. et"f
    // tada treba da se ispise greska jer se ocekuje da se unese \ pre znaka " kako bi interpreter znao da i to zelimo da ispisemo
    if(!spaceUsed){

        if(first == '"' && last == '"'){
            stripQuo(line);
            return true;
        }

        for(size_t i = 1; i < line.size(); ++i) {
            if (line[i - 1] == '\\' && line[i] == '"') {
                line.erase(std::remove(line.begin(), line.end(), '\\'), line.end());
                stripQuo(line);
                return true;
            }
        }

        return false;
        
    }

    // ako je uneto vise reci i nije korisceno " vracamo false
    // ako je uneto vise reci i korisceno manje od 2 " vracamo false
    if(!quotationUsed || numOfQuotationsUsed < 2) return false;

    if(numOfQuotationsUsed > 2) {
        for(size_t i = 1; i < line.size(); ++i) {
            if (line[i - 1] == '\\' && line[i] == '"') {
                line.erase(std::remove(line.begin(), line.end(), '\\'), line.end());
                stripQuo(line);
                return true;
            }
        }
        return  false;
    }

    // uneto vise reci i korisceni ", proveravamo validnost

    if ((first == '"' && last != '"') || (first != '"' && last == '"')) return false;

    stripQuo(line);
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
        std::cout << "Error: no file found";
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

    std::size_t left = line.find_first_not_of(whiteSpace); // prvi karakter koji nije whitespace
    std::size_t right = line.find_last_not_of(whiteSpace); // poslednji karakter koji nije whitespace

    if (left == right) {
        line.clear();
    } else {
        line = line.substr(left, right - left + 1);
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
        char opt = line[pos + 1];
        line = line.substr(pos + 2);
        return opt;
    }
    return '\0';
}
