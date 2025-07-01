#include <stdexcept>
#include <iostream>
#include <string>

class MarketPlaceException : public std::exception
{
private:
    std::string message_;

public:
    explicit MarketPlaceException(const std::string &msg)
        : message_(msg) {}

    const char *what() const noexcept override
    {
        return message_.c_str();
    }
};