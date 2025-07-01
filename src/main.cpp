#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Interface.hpp"

int main()
{
    // Initialize random seed for product IDs
    std::srand(std::time(nullptr));

    std::cout << "Inicializando Marketplace..." << std::endl;

    Interface interface;
    interface.executar();

    return 0;
}