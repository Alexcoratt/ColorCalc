#ifndef VALUE_EXCEPTION_HPP
#define VALUE_EXCEPTION_HPP

#include "EnvironmentException.hpp"

class ValueException : public EnvironmentException {
private:
    char const * _msg;

public:
    inline ValueException(char const * msg) : _msg(msg) {}

    char const * what() const noexcept { return _msg; }
};

#endif