#ifndef VARIABLE_EXCEPTION_HPP
#define VARIABLE_EXCEPTION_HPP

#include <string>

#include "EnvironmentException.hpp"

class VariableException : public EnvironmentException {
private:
    std::string const _msg;

public:
    inline VariableException(std::string const & msg) : _msg(msg) {}
    char const * what() const noexcept { return _msg.c_str(); }
};

#endif