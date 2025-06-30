#include "Usuario.hpp"
#include <iostream>
#include <string>

Usuario::Usuario() {}
Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : nome(nome), email(email), senha(senha){
    }

void Usuario::cadastrar(){
}

bool Usuario::login(std::string email, std::string senha){
}


void Usuario::visualizarPerfil(){
    std::cout << "---------- MEU PERFIL ---------- \n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "CPF/CNPJ: " << cpf_cnpj << "\n";   // ver isso aq sdps
    std::cout << "Endereço: " << endereco << "\n";
    std::cout << "Telefone: " << telefone << "\n";
}


void Usuario::editarPerfil(){
    int opcao;
    std::string novoValor;
    std::cout << "Escolha uma opção:\n";
    std::cout << "1. Editar email \n";
    std::cout << "2. Editar senha \n";
    std::cout << "3. Editar telefone \n";    
    std::cout << "4. Editar endereço \n";

/* FINALIZAR DEPOIAS 
    std::cin >> opcao;
    switch(opcao){
        case 1:
            editarEmail();
            break;
        case 2:
            editarSenha();
            break;
        case 3:
            editarTelefone();
            break;
        case 4: 
            // endereço
            break;
        default:
            std::cout << "Opção inválida." <<std::endl;
    }
*/
}

void Usuario::editarEmail(){
    std::string novoEmail;
    std::cout << "Digite seu novo email: \n"
    std::getline(std::cin, novoEmail);
    email = novoEmail;
    std::cout << "Seu email foi atualizado! \n";
}



void Usuario::editarSenha(){
    std::string novaSenha;
    std::cout << "Digite sua nova senha: \n";
    std::getline(std::cin, novaSenha);
    senha = novaSenha;
    std::cout << "Sua senha foi atualizada! \n";
}


void Usuario::editarTelefone(){
    std::string novoTelefone;
    std::cout << "Digite seu novo número: \n";
    std::getline(std::cin, novoTelefone);
    telefone = novoTelefone;
    std::cout << "Seu telefone foi atualizado. \n";
}


/*
void Usuario::editarEndereco(){
}
*/


bool Usuario::confirmarAcao(){
    char resposta;
    std::cout << "Confirme esta ação (s/n) ";
    std::cin >> resposta;
    std::cin.ignore();
   if (resposta == 's' || resposta == 'S'){
        std::cout << "Ação confirmada \n";
        return true;
    } else {
        std::cout << "Ação cancelada \n";
        return false;
    }
}
