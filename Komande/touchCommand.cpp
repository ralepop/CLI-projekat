#include "touchCommand.h"
#include <fstream>
#include <iostream>
#include <string>

void TouchCommand::execute(std::istream &input, std::ostream &output) {
    
    std::string filename {};
    std::string defaultPath {"../../"};
    
    // while petlja omogucava da kreiramo vise fajlova odjednom
    while(input >> filename){
        std::string fullPath {defaultPath + filename};

        const bool valid {checkLine(fullPath)};

        std::ifstream infile{fullPath};

        if(infile.is_open()) {
            output << "Error: File " << filename << " already exists.\n";
        }else{
            std::ofstream file{fullPath};
        }
    }
    
}