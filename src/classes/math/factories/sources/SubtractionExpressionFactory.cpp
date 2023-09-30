#include "SubtractionExpressionFactory.hpp"

SubtractionExpression * SubtractionExpressionFactory::build(IExpression * left, IExpression * right) const {
    return new SubtractionExpression(left, right);
}

int SubtractionExpressionFactory::getPriority() const { return 2; }