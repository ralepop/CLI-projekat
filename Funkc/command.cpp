#include "command.h"

bool Command::checkLine(std::string &line)
{
    int numWhitespaceLeft {0};
    int numWhitespaceRight {0};
    
    stripWhitespace(line, numWhitespaceLeft, numWhitespaceRight);
    std::cout << numWhitespaceLeft << '\n' << numWhitespaceRight << '\n';
    numWhitespaceRight++;
    line = line.substr(2, line.size() - 4);
    char first {line[0]};
    char last {line[line.length() - 1]};
    bool spaceUsed {false};
    bool quotationUsed {false};
    int numOfQuotationsUsed = 0;

    // proveravamo da li ima space
    for(char c : line){
        if(std::isspace(c)) spaceUsed = true;
        else if(c == '"') {
            quotationUsed = true;
            numOfQuotationsUsed++;
        }
    }

    // ako je uneta samo jedna rec
    if(!spaceUsed && !quotationUsed) return true;

    // ako je uneta samo jedna rec i " znak, npr. et"f
    // tada treba da se ispise greska jer se ocekuje da se unese \ pre znaka " kako bi interpreter znao da i to zelimo da ispisemo
    if(!spaceUsed && quotationUsed){
        char prev {};
        for(char c : line){
            if(prev == '\\' && c == '"'){
                line.erase(std::remove(line.begin(), line.end(), '\\'), line.end());
                stripQuo(line);
                return true;
            }
            prev = c;
        }
        
        if(first == '"' && last == '"'){
            stripQuo(line);
            
            return true;
        } 
        return false;
    }

    // ako je uneto vise reci i nije korisceno " vracamo false
    if(spaceUsed && !quotationUsed) return false;

    // ako je uneto vise reci i korisceno manje od 2 " vracamo false
    if(spaceUsed && numOfQuotationsUsed < 2) return false;

    if(spaceUsed && numOfQuotationsUsed > 2) {
        if(!line.empty() && first == '"' && last == '"'){
            char prev {};
            for(char c : line){
                if(prev == '\\' && c == '"'){
                    line.erase(std::remove(line.begin(), line.end(), '\\'), line.end());
                    stripQuo(line);
                    return true;
                }
                prev = c;
            }
            return false;
        }
    }

    // uneto vise reci i korisceni ", proveravamo validnost
    if(spaceUsed && quotationUsed){

        if((first == '"' && last != '"') || (first != '"' && last == '"')) return false;
        else if(!line.empty() && first == '"' && last == '"'){
            stripQuo(line);
            return true;
        }
    }
            

}

void Command::stripQuo(std::string &line)
{
    line = line.substr(1, line.size() - 2);
}

bool Command::checkIfFile(std::string &line)
{
    // zavrsi
}

void Command::stripWhitespace(std::string &line, int &numWhitespaceLeft, int &numWhitespaceRight)
{
    bool word {false};

    // proveravamo sa leva na desnu
    for(char c : line){
        if(!std::isspace(c)) word = true;
        if(!word) numWhitespaceLeft++;
    }
    
    word = false;

    // proveravamo sa desna na levu
    for(int i = line.size() - 1; i >= 0; --i){
        char c = line[i];
    if(!std::isspace(c)) word = true;
        if(!word) numWhitespaceRight++;
    }
}
