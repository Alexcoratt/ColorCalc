#ifndef DIVISION_EXPRESSION_FACTORY_HPP
#define DIVISION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "DivisionExpression.hpp"
#include "IExpressionFactory.hpp"

class DivisionExpressionFactory : public IExpressionFactory {
public:
    IExpression * build(IExpression * first = 0, IExpression * second = 0) const {
        return new DivisionExpression(first, second);
    }

    int getPriority() const { return 4; }
};

#endif