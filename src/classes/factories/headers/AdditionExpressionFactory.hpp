#ifndef ADDITION_EXPRESSION_FACTORY_HPP
#define ADDITION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "AdditionExpression.hpp"
#include "IExpressionFactory.hpp"

class AdditionExpressionFactory : public IExpressionFactory {
public:
    IExpression * build(IExpression * first = 0, IExpression * second = 0) const {
        return new AdditionExpression(first, second);
    }

    int getPriority() const { return 1; }
};

#endif