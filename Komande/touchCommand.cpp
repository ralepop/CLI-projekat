#include "touchCommand.h"
#include <fstream>
#include <iostream>
#include <string>

void TouchCommand::execute(std::string &argument, std::ostream &output) {
    
    std::string fullPath {defaultPath + argument};

    const bool valid {checkLine(fullPath)};

    std::ifstream infile{fullPath};

    if(infile.is_open()) {
        output << "Error: File " << argument << " already exists.\n";
    }else{
        std::ofstream file{fullPath};
    }

    
}