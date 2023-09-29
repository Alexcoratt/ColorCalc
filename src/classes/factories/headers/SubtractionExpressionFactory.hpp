#ifndef SUBTRACTION_EXPRESSION_FACTORY_HPP
#define SUBTRACTION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "SubtractionExpression.hpp"
#include "IExpressionFactory.hpp"

class SubtractionExpressionFactory : public IExpressionFactory {
public:
    IExpression * build(IExpression * first = 0, IExpression * second = 0) const {
        return new SubtractionExpression(first, second);
    }

    int getPriority() const { return 2; }
};

#endif