#include <algorithm>

#include "RemoveVariableFunctionFactory.hpp"
#include "VariableExpression.hpp"
#include "ExpressionException.hpp"

RemoveVariableFunctionFactory::RemoveVariableFunctionFactory(Environment * env) : _env(env) {}
RemoveVariableFunctionFactory::RemoveVariableFunctionFactory(RemoveVariableFunctionFactory const & other) : _env(other._env) {}

RemoveVariableFunctionFactory & RemoveVariableFunctionFactory::operator=(RemoveVariableFunctionFactory const & other) {
  if (this != &other) {
    RemoveVariableFunctionFactory tmp(other);
    swap(tmp);
  }
  return *this;
}

RemoveVariableFunctionFactory::~RemoveVariableFunctionFactory() {}

void RemoveVariableFunctionFactory::swap(RemoveVariableFunctionFactory & other) {
  std::swap(_env, other._env);
}

RemoveVariableFunction * RemoveVariableFunctionFactory::build(IExpression *, IExpression * right) const {
  VariableExpression * var = dynamic_cast<VariableExpression *>(right);
  if (!var)
    throw ExpressionException("Variable removal exception: operand must be a variable");
  return new RemoveVariableFunction(_env, var->getName());
}
