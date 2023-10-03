#ifndef EXPRESSION_EXCEPTION_HPP
#define EXPRESSION_EXCEPTION_HPP

#include <string>

#include "MathException.hpp"

class ExpressionException : public MathException {
private:
    std::string const _msg;

public:
    inline ExpressionException(std::string const & msg) : _msg(msg) {
    }

    char const * what() const noexcept {
        return _msg.c_str();
    }
};

#endif