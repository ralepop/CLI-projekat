#include "command.h"
#include "commandFactory.h"

#include <cctype>
#include <cstddef>
#include <ostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


bool Command::newlineExist(const std::string &line){
    return(line.find('\n') != std::string::npos);
}

void Command::splitNewline(const std::string &line, std::vector<std::string> &lines){
    size_t start = 0, end = line.find('\n');

    while(end != std::string::npos){
        lines.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find('\n', start); // nalazimo sledeci '\n'
    }
    
    lines.push_back(line.substr(start, line.length() - start));
}


bool Command::checkLine(std::string &line){

    if(line.empty()) return false;

    const size_t firstQuo = line.find_first_of('"'), lastQuo = line.find_last_of('"');

    // ukoliko nema dva navodnika
    if(firstQuo == std::string::npos || lastQuo == std::string::npos || firstQuo == lastQuo){
        for(const char &ch : line){
            if(std::isspace(ch)) return false;
        }
        return true;
    }

    // proverava da li ima nesto pre ili posle navodnika
    if(firstQuo != 0 || lastQuo != line.size() - 1) return false;

    const std::string argument = line.substr(firstQuo + 1, lastQuo - firstQuo - 1);
    if(argument.empty()) return false;
    line = argument;

    return true;
}

bool Command::checkIfFile(std::string &line, const std::string& filetype){
    if(line.size() < filetype.size() + 1) return false;

    const size_t pos = line.find('<'); // trazimo poziciju ulaznog znakovnog toka
    if(pos != std::string::npos){ // proveravamo da li ulazni znakovni tok uopste postoji
        line = line.substr(pos + 1, line.length()); // skidamo znak '<'
        stripWhitespace(line);
    }

    return line.ends_with('.' + filetype);
}

std::string Command::putIntoString(const std::string& line){
    std::ifstream file(line);

    if(!file.is_open()){
        std::cout << "Error: No file found\n";
        return "";
    }

    std::string text, temp;

    while(std::getline(file, temp)){
        text += temp + '\n';
    }

    return text;
}

void Command::stripWhitespace(std::string &line){

    if(line.empty()) return;

    const char* whiteSpace = " \t\n";

    const std::size_t left = line.find_first_not_of(whiteSpace); // prvi karakter koji nije whitespace
    const std::size_t right = line.find_last_not_of(whiteSpace); // poslednji karakter koji nije whitespace

    if(left == right) line = line.substr(left, 1);
    else line = line.substr(left, right - left + 1);
}

void Command::processCommand(std::vector<std::string> &inputs, std::string &inputLine, std::string &prompt, std::ostream &output, std::ostringstream &outputBuffer){

    bool isFirst = true, isLast = false;
    std::string lastResult;
    size_t start = 0, end;

    for(const std::string &input : inputs){

        // proveravamo da li je prvi input u pitanju
        // ako jeste onda mora da sadrzi argument bez obzira da li ima cevovod ili ne
        if(isFirst && input != inputs[0]) isFirst = false;
        if(!isLast && input == inputs.back()) isLast = true;

        std::istringstream inputStream(input);
        std::string commandName;
        inputStream >> commandName;

        const auto command = CommandFactory::createCommand(commandName);

        if(!command){
            if(Command::errorHandling(input)) std::cout << "Unknown command: \"" << commandName << "\".\n";
            continue;
        }

        std::string opt, arg;

        if(command->doesTakeOpt() && command->getName() != "tr"){
            inputStream >> opt;
            if(opt.empty()){
                std::cout << "Erorr: Invalid -opt\n";
                continue;
            }
        }

        std::getline(inputStream, arg);
        Command::stripWhitespace(arg);

        // ako treba da se unese vise linija
        if(arg.empty() && command->doesTakeArg() && !Command::pipeExist(inputLine)){
            std::string additionalLine;
            while(true){
                std::getline(std::cin, additionalLine);
                if(additionalLine.empty()) break;
                arg += (arg.empty() ? "" : "\n") + additionalLine;
            }
        }

        // posebni slucajevi komandi
        if(command->getName() == "prompt"){
            if(!arg.empty()) prompt = arg;
            continue;
        }else if(command->getName() == "batch"){
            std::vector<std::string> commands = Command::splitString(arg, '\n');
            processCommand(commands, inputLine, prompt, output, outputBuffer);
        }

        bool rediExist = Command::redirectExist(input);

        command->execute(opt, arg, output, rediExist, lastResult);

        if(isLast && inputs.size() > 1){
            if(command->getName() == "echo"){
                std::cout << lastResult << '\n';
                break;
            }
        }

        end = outputBuffer.str().rfind('\n');

        if(end != std::string::npos){
            lastResult = outputBuffer.str().substr(start, end - start);
            start = end + 1;
        }
    }
}

std::vector<std::string> Command::splitString(const std::string &line, char c){
    std::vector<std::string> result;
    std::string temp;
    size_t start = 0, end = 0;

    while((end = line.find(c, start)) != std::string::npos ){
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

void Command::createFile(std::string &filename, std::ostream &output){
    std::ifstream infile(filename);

    if(infile.is_open()){
        output << "Error: File " << filename << " already exists.\n";
        return;
    }

    std::ofstream file(filename);

    if(!file) output << "Error: Could not create the file " << filename << ".\n";
}

bool Command::redirectExist(const std::string &line){
    return line.find('>') != std::string::npos;
}

std::string Command::redirectProcess(std::string &line, bool &doubleRedirect){

    const size_t posTxt = line.find(".txt");

    if(posTxt != std::string::npos){
        size_t pos = line.rfind(">>", posTxt);
        doubleRedirect = (pos != std::string::npos) ? true : false;

        if(!doubleRedirect) pos = line.rfind(">", posTxt);
        std::string redirectFile = line.substr(pos + (doubleRedirect ? 2 : 1), posTxt - pos + 4);

        line = line.substr(0, pos);
        stripWhitespace(line);
        stripWhitespace(redirectFile);

        return redirectFile;
    }

    return "";
}

bool Command::pipeExist(const std::string &line){
    return line.find('|') != std::string::npos;
}

bool Command::errorHandling(const std::string &line){
    const std::string validSymbols = "-\"<>.|: ";
    bool isFine = true;

    std::vector<size_t> errorPositions;

    for(size_t i = 0; i < line.length(); ++i){

        char c = line[i];
        if(!std::isalnum(c) && validSymbols.find(c) == std::string::npos) errorPositions.push_back(i);
    }

    if(!errorPositions.empty()){
        std::cout << "Error - unexpected characters:\n" << line << '\n';
        isFine = false;

        for(size_t i = 0; i < line.length(); ++i){
            std::cout << (std::find(errorPositions.begin(), errorPositions.end(), i) != errorPositions.end() ? '^' : ' ');
        }
        std::cout << '\n';
    }

    return isFine;
}
