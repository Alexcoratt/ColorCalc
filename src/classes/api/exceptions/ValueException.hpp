#ifndef VALUE_EXCEPTION_HPP
#define VALUE_EXCEPTION_HPP

#include <string>

#include "EnvironmentException.hpp"

class ValueException : public EnvironmentException {
private:
    std::string const _msg;

public:
    inline ValueException(std::string const & msg) : _msg(msg) {}
    char const * what() const noexcept { return _msg.c_str(); }
};

#endif