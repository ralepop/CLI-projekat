#include "trCommand.h"

#include <_stdio.h>
#include <cstddef>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void TrCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){

    // tr str1 str2 str3

    std::vector<std::string> strings;
    std::string temp, redirectFile, text;
    bool insideQuotes = false, doubleRedirect = false, valid = true;

    if(redirectExist) redirectFile = redirectProcess(argument, doubleRedirect);

    const bool isFile = checkIfFile(argument, "txt");

    if(isFile){
        argument = putIntoString(argument);
        if(argument.empty()) return;
    }

    const size_t firstQuo = argument.find_first_of('"'), lastQuo = argument.find_last_of('"');
    if(firstQuo != std::string::npos && lastQuo != std::string::npos && firstQuo == lastQuo && !isFile){
        output << "Error: Invalid input\n";
        return;
    }

    if(!lastResult.empty() && pipeExist){
        strings.push_back(lastResult);
        lastResult.clear();
    }

    for(size_t i = 0; i < argument.size(); i++){
        char c = argument[i];

        if(c == '"') insideQuotes = !insideQuotes;
        else if(std::isspace(c) && !insideQuotes){
            if(!temp.empty()){
                strings.push_back(temp);
                temp.clear();
            }
        }else temp.push_back(c);
    }

    if(!temp.empty()) strings.push_back(temp);

    bool onlyDeletion = false; // znaci da je unet samo str1 i samo vrsimo brisanje karaktera

    // moramo da proverimo da li je unet samo str1 i onda hvatamo linije
    if(strings.size() == 1){
        onlyDeletion = true;
        std::string additionalLine;
        while(true){
            std::getline(std::cin, additionalLine);
            if(additionalLine.empty()) break;
            strings.push_back(additionalLine);
        }
    }

    if(strings.size() == 2 && !onlyDeletion) onlyDeletion = true;

    if(onlyDeletion){ // ukoliko radimo samo brisanje karatera
        std::string rez;
        for(size_t i = 1; i < strings.size(); i++){
            for(char c : strings[i]){
                if(strings[0].find(c) == std::string::npos) rez += c; // ukoliko nadje karakter ne dodaje ga u rez
            }
            strings[i] = rez;
            rez.clear();
        }

        for(size_t i = 1; i < strings.size(); i++){
            lastResult += strings[i];
            if(i + 1 < strings.size()) lastResult += '\n';
        }

    }else{ // ukoliko se radi klasicna tr komanda
        std::string rez;
        if(strings.size() < 2 || strings.size() > 3){
            std::cout << "Error: Invalid number of arguments for tr command\n";
            return;
        }
    
        std::unordered_map<char, char> strMap;
        
        // kreiranje mape str2 u str3
        for(size_t i = 0; i < strings[1].size(); ++i){
            char temp = (i < strings[2].size() ? strings[2][i] : strings[2].back()); // ukoliko je str2 duzi od str3 produzavamo poslednji char
            strMap[strings[1][i]] = temp;
        }
    
        for(size_t i = 0; i < strings[0].size(); ++i){
            if(strMap.find(strings[0][i]) != strMap.end()) strings[0][i] = strMap[strings[0][i]];
        }
        
        lastResult = strings[0];
    }

    if(redirectExist && !redirectFile.empty()){ // u fajl jer postoji redirect znak

        std::ofstream file(redirectFile, std::ios::out);
        file << lastResult;
        output << lastResult;

        if(doubleRedirect){

            output << lastResult << std::endl;
            file << lastResult;

        }else output << std::endl;

        file.close();

    }else if(!pipeExist ||(pipeExist && isLast)) output << lastResult << std::endl;
}