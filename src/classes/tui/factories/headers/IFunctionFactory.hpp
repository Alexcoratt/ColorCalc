#ifndef I_FUNCTION_FACTORY_HPP
#define I_FUNCTION_FACTORY_HPP

#include <vector>
#include "IFunction.hpp"
#include "IValue.hpp"
#include "Environment.hpp"

class IFunctionFactory {
public:
    virtual ~IFunctionFactory() {};
    virtual IFunction * build(Environment *, std::vector<IValue *> const &) = 0;
};

#endif