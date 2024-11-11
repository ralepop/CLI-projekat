#include "touchCommand.h"

void TouchCommand::execute(std::istream &input, std::ostream &output) {
    std::string filename;
    input >> filename;

    std::ifstream infile(filename);
    if(infile.is_open()) {
        std::cerr << "Error: File already exists.\n";
    }else{
        std::ofstream file(filename);
    }
}