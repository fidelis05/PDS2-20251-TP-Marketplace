#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include <stdexcept>
#include <string>

class RunTimeException : public std::runtime_error
{
public:
    explicit RunTimeException(const std::string &message)
        : std::runtime_error(message) {}
};

#endif