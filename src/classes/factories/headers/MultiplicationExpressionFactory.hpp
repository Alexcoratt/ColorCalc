#ifndef MULTIPLICATION_EXPRESSION_FACTORY_HPP
#define MULTIPLICATION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "MultiplicationExpression.hpp"
#include "IExpressionFactory.hpp"

class MultiplicationExpressionFactory : public IExpressionFactory {
public:
    IExpression * build(IExpression * first = 0, IExpression * second = 0) const {
        return new MultiplicationExpression(first, second);
    }

    int getPriority() const { return 3; }
};

#endif