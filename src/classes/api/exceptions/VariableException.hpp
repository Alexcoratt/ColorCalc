#ifndef VARIABLE_EXCEPTION_HPP
#define VARIABLE_EXCEPTION_HPP

#include "EnvironmentException.hpp"

class VariableException : public EnvironmentException {
private:
    char const * _msg;

public:
    inline VariableException(char const * msg) : _msg(msg) {}
    char const * what() const noexcept { return _msg; }
};

#endif