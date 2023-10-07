#ifndef DIVISION_EXPRESSION_FACTORY_HPP
#define DIVISION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "DivisionExpression.hpp"
#include "IExpressionFactory.hpp"

class DivisionExpressionFactory : public IExpressionFactory {
public:
    DivisionExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif