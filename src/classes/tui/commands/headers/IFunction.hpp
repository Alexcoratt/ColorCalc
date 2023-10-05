#ifndef I_FUNCTION_HPP
#define I_FUNCTION_HPP

#include "IValue.hpp"

class IFunction {
public:
    virtual ~IFunction() {}

    virtual IValue * exec() = 0;
};

#endif