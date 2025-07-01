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

class AdminException : public MarketPlaceException
{
public:
    explicit AdminException(const std::string &msg)
        : MarketPlaceException(msg) {};
};

class UsuarioException : public MarketPlaceException
{
public:
    explicit UsuarioException(const std::string &msg)
        : MarketPlaceException(msg) {};
};