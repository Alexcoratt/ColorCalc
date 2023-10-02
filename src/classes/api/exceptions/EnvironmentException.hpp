#ifndef ENVIRONMENT_EXCEPTION_HPP
#define ENVIRONMENT_EXCEPTION_HPP

#include <exception>

class EnvironmentException : public std::exception {
    char const * what() const noexcept {
        return "Environment exception";
    }
};

#endif