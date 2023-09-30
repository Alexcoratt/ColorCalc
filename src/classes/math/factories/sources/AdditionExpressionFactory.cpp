#include "AdditionExpressionFactory.hpp"

AdditionExpression * AdditionExpressionFactory::build(IExpression * left, IExpression * right) const {
    return new AdditionExpression(left, right);
}

int AdditionExpressionFactory::getPriority() const { return 1; }