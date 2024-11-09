#include <iostream>

int main()
{
    int number;
    std::cout << "Unesite broj: ";
    std::cin >> number;  // Koristi std::istream objekat std::cin za unos
    std::cout << "Uneli ste broj: " << number << std::endl;
    return 0;
}