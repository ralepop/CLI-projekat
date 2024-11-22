#include "touchCommand.h"

void TouchCommand::execute(std::istream &input, std::ostream &output) {
    
    std::string filename {};
    
    // while petlja omogucava da kreiramo vise fajlova odjednom
    while(input >> filename){
        std::ifstream infile{filename};

        if(infile.is_open()) {
            output << "Error: File " << filename << " already exists.\n";
        }else{
            std::ofstream file{filename};
        }
    }
    
}