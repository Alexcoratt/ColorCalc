#ifndef MATH_EXCEPTION_HPP
#define MATH_EXCEPTION_HPP

#include <exception>

class MathException : public std::exception {
    char const * what() const noexcept {
        return "Math exception";
    }
};

#endif