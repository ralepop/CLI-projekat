#ifndef command_h
#define command_h


#include <istream>
#include <iostream>
#include <fstream>

// klasa Command predstavlja osnovnu strukturu svih komandi

class Command
{

public:

    // std::istream &input prima referencu na ulazni tok 
    // input moze da bude std::cin, fajl ili neka druga vrsta podataka

    // std::ostream &output prima referencu na izlazni tok
    // output moze da bude std::cout, fajl ili neka druga vrsta podataka
    virtual void execute(std::istream &input, std::ostream &output) = 0;

    // proverava da li je string unet na validan nacin
    static bool checkLine(std::string &line);

    // skida quotation sa pocetka i kraja
    static void stripQuo(std::string &line);

    // proverava da li je uneti string fajl, trenutno podrzava samo .txt fajl
    static bool checkIfFile(std::string &line, const std::string& filetype);

    // smesta sadrzaj fajla u string
    static std::string putIntoString(const std::string& line);

    // skida beline sa leve i desne strane
    static void stripWhitespace(std::string &line);

    virtual ~Command() = default;
};

#endif

