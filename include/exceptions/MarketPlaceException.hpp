#include <stdexcept>
#include <iostream>
#include <string>

class MarketPlaceException : public std::runtime_error
{

public:
    explicit MarketPlaceException(const std::string &msg)
        : std::runtime_error(msg) {}
};

class CorreiosException : public MarketPlaceException
{
public:
    explicit CorreiosException(const std::string &msg)
        : MarketPlaceException(msg) {}
};

class ProdutoException : public MarketPlaceException
{
public:
    explicit ProdutoException(const std::string &msg)
        : MarketPlaceException(msg) {};
};

class PedidoException : public MarketPlaceException
{
public:
    explicit PedidoException(const std::string &msg)
        : MarketPlaceException(msg) {};
};