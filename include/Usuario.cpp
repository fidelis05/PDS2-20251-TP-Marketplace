#include "Usuario.hpp"
#include <iostream>

Usuario::Usuario() {}
Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : nome(nome), email(email), senha(senha) {}

