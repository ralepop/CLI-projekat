#ifndef command_h
#define command_h


#include <iostream>
#include <string>

const std::string defaultPath = "../";

const int MAX_LENGTH = 512;

// klasa Command predstavlja osnovnu strukturu svih komandi

class Command {

protected:

    bool takesArg = true;
    bool takesOpt = false;


public:

    // konstruktor, explicit osigurava pravilan poziv konstruktora i izbegava implicitne konverzije
    explicit Command(bool t_takesArg = true, bool t_takesOpt = false) :
    takesArg(t_takesArg),
    takesOpt(t_takesOpt)
    {}

    // std::istream &input prima referencu na ulazni tok 
    // input moze da bude std::cin, fajl ili neka druga vrsta podataka

    // std::ostream &output prima referencu na izlazni tok
    // output moze da bude std::cout, fajl ili neka druga vrsta podataka
    virtual void execute(char &opt, std::string &argument, std::ostream &output) = 0;

    // proverava da li je string unet na validan nacin
    static bool checkLine(std::string &line);

    // skida quotation sa pocetka i kraja
    static void stripQuo(std::string &line);

    // proverava da li je uneti string fajl (.txt fajl)
    static bool checkIfFile(const std::string &line, const std::string& filetype);

    // smesta sadrzaj fajla u string
    static std::string putIntoString(const std::string &line);

    // skida beline sa leve i desne strane
    static void stripWhitespace(std::string &line);

    // vraca naziv komande i sece liniju do kraja komande
    static std::string commandName(std::string &line);

    // vraca naziv -opt (ako postoji) i sece liniju do kraja -opt
    static char opt(std::string &line);

    bool doesTakeArg() const {
        return takesArg;
    }

    bool doesTakeOpt() const {
        return takesOpt;
    }

    // destruktor
    virtual ~Command() = default;
};

#endif

