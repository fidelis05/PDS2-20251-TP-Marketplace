#include "Correios.hpp"
#include <ctime>
#include "Pedido.hpp"
#include "exceptions/RunTimeException.hpp"

int Correios::setStatus(int n)
{
    if (n < 8)
    {
        if (n <= 3)
        {
            if (this->codigoRastreio == 0)
            {
                throw RunTimeException("Favor informe o Código de Rastreio antes de Prosseguir");
                return -1;
            }
            else
            {
                this->statusInfo = this->status.status_map[n];
            }
        }
        else
        {
            this->statusInfo = this->status.status_map[n];
        }
    }
    else
    {
        throw RunTimeException("Defina um número válido");
        return -1;
    }

    if (n == 7)
    {
        this->dataEntrega = std::time(nullptr);
    }
    return 0;
}

int Correios::setcodigoRastreio(int x)
{
    this->codigoRastreio = x;
    return 0;
}

int Correios::getLista()
{
    return 0;
}
