#include <istream>
#ifndef command_h
#define command_h

// klasa Command predstavlja osnovnu strukturu svih komandi

class Command
{
// protected:

//     std::string commandName;

public:

    // std::istream &input prima referencu na ulazni tok 
    // input moze da bude std::cin, fajl ili neka druga vrsta podataka

    // std::ostream &output prima referencu na izlazni tok
    // output moze da bude std::cout, fajl ili neka druga vrsta podataka

    virtual void execute(std::istream &input, std::ostream &output) = 0;

    virtual ~Command() = default;

};

#endif