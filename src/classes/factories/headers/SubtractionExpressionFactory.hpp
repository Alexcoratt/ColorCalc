#ifndef SUBTRACTION_EXPRESSION_FACTORY_HPP
#define SUBTRACTION_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"
#include "SubtractionExpression.hpp"
#include "IExpressionFactory.hpp"

class SubtractionExpressionFactory : public IExpressionFactory {
public:
    SubtractionExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif