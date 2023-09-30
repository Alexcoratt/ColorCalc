#include "MultiplicationExpressionFactory.hpp"

MultiplicationExpression * MultiplicationExpressionFactory::build(IExpression * left, IExpression * right) const {
    return new MultiplicationExpression(left, right);
}

int MultiplicationExpressionFactory::getPriority() const { return 3; }