#include "DivisionExpressionFactory.hpp"

DivisionExpression * DivisionExpressionFactory::build(IExpression * left, IExpression * right) const {
    return new DivisionExpression(left, right);
}

int DivisionExpressionFactory::getPriority() const { return 4; }