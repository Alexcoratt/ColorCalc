#ifndef EXPRESSION_EXCEPTION_HPP
#define EXPRESSION_EXCEPTION_HPP

#include "MathException.hpp"

class ExpressionException : public MathException {
private:
    char const * _answer;

public:
    inline ExpressionException(char const * answer) : _answer(answer) {}

    char const * what() const noexcept {
        return _answer;
    }
};

#endif