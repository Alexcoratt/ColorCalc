#include "RemoveVariableFunctionFactory.hpp"

RemoveVariableFunction * RemoveVariableFunctionFactory::build(Environment * env, std::vector<IValue *> const & args) {
    return new RemoveVariableFunction(env, args[0]->getStringValue());
}