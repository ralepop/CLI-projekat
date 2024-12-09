#include "touchCommand.h"

#include <fstream>
#include <string>

void TouchCommand::execute(char &opt, std::string &argument, std::ostream &output) {
    
    std::string fullPath {defaultPath + argument};

    std::ifstream infile{fullPath};

    if(infile.is_open()) {
        output << "Error: File " << argument << " already exists.\n";
    }else{
        std::ofstream file{fullPath};
    }

    
}