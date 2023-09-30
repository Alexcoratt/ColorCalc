#ifndef ADDITION_EXPRESSION_FACTORY_HPP
#define ADDITION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "AdditionExpression.hpp"
#include "IExpressionFactory.hpp"

class AdditionExpressionFactory : public IExpressionFactory {
public:
    AdditionExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif