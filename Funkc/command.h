#ifndef command_h
#define command_h

#include <iostream>
#include <string>

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
    virtual void execute(char &opt, std::string &argument, std::ostream &output, bool &redirectExist) = 0;


    static void splitNewline(const std::string &line, std::vector<std::string> &lines);

    // proverava da li je string unet na validan nacin
    static bool checkLine(std::string &line);

    // skida quotation sa pocetka i kraja
    static void stripQuo(std::string &line);

    // proverava da li je uneti string fajl (.txt fajl)
    static bool checkIfFile(std::string &line, const std::string &filetype);

    // smesta sadrzaj fajla u string
    static std::string putIntoString(const std::string &line);

    // skida beline sa leve i desne strane
    static void stripWhitespace(std::string &line);

    // kreira fajl
    static void createFile(std::string &filename, std::ostream &output);

    // splituje string u odnosu na char c i stavlja u vector
    // u slucaju: time | tr ":" "." | wc -c > time.txt, char c bi bio '|'
    // pa bi vector[0] = "time"
    // vector[1] = "tr ":" ".""
    // vector[2] = "wc -c > time.txt"
    static std::vector<std::string> splitString(const std::string &line, char c);

    // vraca naziv komande i sece liniju do kraja komande
    static std::string commandName(std::string &line);

    // vraca naziv -opt (ako postoji) i sece liniju do kraja -opt
    static char opt(std::string &line);

    // proverava da li je unos u nekoliko redova
    static bool newlineExist(const std::string &line);

    // proverava da li u stringu ima razmaka
    static bool whitespaceExist(const std::string &line);

    // proverava da li linija sadrzi preusmerenje (redirect)
    static bool redirectExist(const std::string &line);

    // sece liniju nakon '>' znaka i vraca fajl za redirect u obliku stringa
    static std::string redirectProcess(std::string &line, bool &doubleRedirect);

    // broji koliko cevovoda (pipe) linija sadrzi, ukoliko nema vraca nulu
    static bool pipeExist(const std::string &line);


    static void pipeProcess(const std::string &line);

    // proverava da li ima nedozvoljenih karatkera i stavlja ^ ispod ukoliko ima
    // vraca true ako je sve u redu, vraca false ako je nasao barem jedan nedozvoljen karakter
    static bool errorHandling(const std::string &line);


    bool doesTakeArg() const {
        return takesArg;
    }

    bool doesTakeOpt() const {
        return takesOpt;
    }

    // destruktor
    virtual ~Command() = default;

    virtual std::string getName() const = 0;
};

#endif

