#include "truncateCommand.h"

#include "command.h"
#include "fstream"

void TruncateCommand::execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) {

    std::ofstream file(argument, std::ios::trunc);
    if (!file) {
        output << "Error: no file found\n";
    }
}