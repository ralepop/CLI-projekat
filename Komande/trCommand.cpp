#include "trCommand.h"

#include <cstddef>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void TrCommand::execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult, bool &pipeExist, bool &isFirst, bool &isLast){

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

    for(size_t i = 0; i < argument.size(); i++){
        char c = argument[i];

        if(c == '"') insideQuotes = !insideQuotes;
        else if(std::isspace(c) && !insideQuotes){
            if(!temp.empty()){
                strings.push_back(temp);
                temp.clear();
            }
        }
        else temp.push_back(c);
    }

    if(!temp.empty()) strings.push_back(temp);
    
    if(strings.size() < 2){
        std::cout << "Error: Not enought arguments for tr command\n";
        return;
    }else if(strings.size() > 3 || (!lastResult.empty() && strings.size() == 3)){
        std::cout << "Error: Too many arguments for tr command\n";
        return;
    }

    std::string str1, str2, str3;

    if(strings.size() == 2){
        str1 = lastResult;
        str2 = strings[0];
        str3 = strings[1];
    }else{
        str1 = strings[0];
        str2 = strings[1];
        str3 = strings[2];
    }


    std::unordered_map<char, char> strMap;

    // kreiranje mape str2 u str3
    for(size_t i = 0; i < str2.size(); ++i){
        char temp = (i < str3.size() ? str3[i] : str3.back()); // ukoliko je str2 duzi od str3 produzavamo poslednji char
        strMap[str2[i]] = temp;
    }

    std::string rez = str1;
    for(size_t i = 0; i < rez.size(); ++i){
        if(strMap.find(rez[i]) != strMap.end()) rez[i] = strMap[rez[i]];
    }

    if(redirectExist && !redirectFile.empty()){ // u fajl jer postoji redirect znak
        std::ofstream file(redirectFile, std::ios::out);
        file << rez;
        output << rez;
        if(doubleRedirect){
            output << rez << std::endl;
            file << rez;
        }else output << std::endl;
        file.close();
    }else if(!pipeExist ||(pipeExist && isLast)){
        output << rez << std::endl;
    }
    lastResult = rez;
}