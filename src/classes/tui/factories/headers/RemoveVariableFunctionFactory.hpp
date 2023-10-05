#ifndef REMOVE_VARIABLE_FUNCTION_FACTORY_HPP
#define REMOVE_VARIABLE_FUNCTION_FACTORY_HPP

#include "IFunctionFactory.hpp"
#include "RemoveVariableFunction.hpp"

class RemoveVariableFunctionFactory : public IFunctionFactory {
public:
    RemoveVariableFunction * build(Environment *, std::vector<IValue *> const &);
};

#endif