#ifndef command_h
#define command_h

#include <iostream>
#include <string>
#include <cctype>
#include <cstddef>
#include <ostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

// klasa Command predstavlja osnovnu strukturu svih komandi

class Command {

protected:

    bool takesArg = true;
    bool takesOpt = false;

public:

    // Konstruktor, takesArg i takesOpt definise da li komanda prima argument ili opt parametar
    explicit Command(bool t_takesArg = true, bool t_takesOpt = false) :
    takesArg(t_takesArg),
    takesOpt(t_takesOpt)
    {}

    // Proverava da li komanda uzima argument
    inline bool doesTakeArg() const { return takesArg; }

    // Proverava da li komanda uzima opt
    inline bool doesTakeOpt() const { return takesOpt; }

    // Proverava da li string 'line' predstavlja putanju do fajla tipa 'filetype'
    // Uklanja znak ulaznog znakovnog toka (<) ako ga pronadje
    static bool checkIfFile(std::string &line, const std::string &filetype);

    // Proverava validnost stringa 'line' i ako treba modifikuje ga
    static bool checkLine(std::string &line);

    // Proverava da li ima nedozvoljenih karatkera i ispisuje ^ ispod svakog ukoliko ima
    // Vraca true ako je sve u redu, vraca false ako je nasao barem jedan nedozvoljen karakter
    static bool errorHandling(const std::string &line);

    // proverava da li je unos u nekoliko redova
    static bool newlineExist(const std::string &line);

    // broji koliko cevovoda(pipe) linija sadrzi, ukoliko nema vraca nulu
    static bool pipeExist(const std::string &line);

    // proverava da li linija sadrzi preusmerenje(redirect)
    static bool redirectExist(const std::string &line);

    // smesta sadrzaj fajla u string
    static std::string putIntoString(const std::string &line);

    // sece liniju nakon '>' znaka i vraca fajl za redirect u obliku stringa
    static std::string redirectProcess(std::string &line, bool &doubleRedirect);

    // splituje string u odnosu na char c i stavlja u vector
    // u slucaju: time | tr ":" "." | wc -c > time.txt, char c bi bio '|'
    // pa bi vector[0] = "time"
    // vector[1] = "tr ":" ".""
    // vector[2] = "wc -c > time.txt"
    static std::vector<std::string> splitString(const std::string &line, char c);

    // kreira fajl
    static void createFile(std::string &filename, std::ostream &output);

    // procesuira unos i stvara komandu
    static void processCommand(std::vector<std::string> &inputs, std::string &inputLine, std::string &prompt, std::ostream &output, std::ostringstream &outputBuffer);

    // delimo unos na nove linije i svaku liniju ubacujemo u vektor lines
    static void splitNewline(const std::string &line, std::vector<std::string> &lines);

    // skida beline sa leve i desne strane
    static void stripWhitespace(std::string &line);

    virtual std::string getName() const = 0;

    // std::istream &input prima referencu na ulazni tok 
    // input moze da bude std::cin, fajl ili neka druga vrsta podataka

    // std::ostream &output prima referencu na izlazni tok
    // output moze da bude std::cout, fajl ili neka druga vrsta podataka
    virtual void execute(std::string &opt, std::string &argument, std::ostream &output, bool &redirectExist, std::string &lastResult) = 0;

    // Destruktor
    virtual ~Command() = default;

};

#endif

