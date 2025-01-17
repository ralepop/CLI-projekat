#include "commandInterpreter.h"

#include <sstream>

constexpr size_t MAX_LINE_SIZE = 512;

void CommandInterpreter::start(){

    while (true) {
        std::cout << prompt << ' ';

        // citamo celu liniju
        std::string inputLine;
        std::getline(std::cin, inputLine);

        if (inputLine.empty()) break;

        if (inputLine.length() > MAX_LINE_SIZE) {
            inputLine = inputLine.substr(0, MAX_LINE_SIZE);
        }

        std::vector<std::string> inputs;

        if (Command::pipeExist(inputLine)) {
            inputs = Command::splitString(inputLine, '|');
        } else {
            inputs.push_back(inputLine);
        }

        // input = "time | tr ":" "." | wc -c > time.txt"
        // arg   = "| tr ":" "." | wc -c > time.txt"

        std::ostringstream outputBuffer; // cuva izlaz komande
        bool isFirst = true;
        std::string lastResult;


        for (const std::string &input : inputs) {

            // proveravamo da li je prvi input u pitanju
            // ako jeste onda mora da sadrzi argument bez obzira da li ima cevovod ili ne
            if (isFirst && input != inputs[0]) isFirst = false;

            std::istringstream inputStream(input);
            std::string commandName;
            inputStream >> commandName;

            const auto command = CommandFactory::createCommand(commandName);

            if (!command) {
                if (Command::errorHandling(inputLine)) {
                    std::cout << "Error: Unknown command \"" << commandName << "\".\n";
                }
                continue;
            }

            std::string opt, arg;

            if (command->doesTakeOpt() && commandName != "tr") {
                inputStream >> opt;
                if (opt.empty()) {
                    std::cout << "Erorr: Invalid -opt\n";
                    continue;
                }
            }

            std::getline(inputStream, arg);
            Command::stripWhitespace(arg);

            // ako treba da se unese vise linija
            if (arg.empty() && command->doesTakeArg() && !Command::pipeExist(inputLine)) {
                std::string additionalLine;
                while (true) {
                    std::getline(std::cin, additionalLine);
                    if (additionalLine.empty()) break;
                    arg += (arg.empty() ? "" : "\n") + additionalLine;
                }
            }

            // ukoliko nije prvi za argument uzimamo output iz prosle iteracije
            if (command->doesTakeArg() && !isFirst) {
                arg = lastResult;
            }


            if (command->getName() == "prompt") {
                if (!arg.empty()) {
                    prompt = arg;
                }
                continue;
            }

            bool rediExist = Command::redirectExist(input);

            std::ostream& output = (inputs.size() > 1) ? outputBuffer : std::cout;

            command->execute(opt[1], arg, output, rediExist);

            lastResult = outputBuffer.str();
        }

    }

}
