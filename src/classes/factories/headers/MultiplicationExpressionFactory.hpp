#ifndef MULTIPLICATION_EXPRESSION_FACTORY_HPP
#define MULTIPLICATION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "MultiplicationExpression.hpp"
#include "IExpressionFactory.hpp"

class MultiplicationExpressionFactory : public IExpressionFactory {
public:
    MultiplicationExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif