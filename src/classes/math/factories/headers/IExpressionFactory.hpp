#ifndef I_EXPRESSION_FACTORY_HPP
#define I_EXPRESSION_FACTORY_HPP

#include "IExpression.hpp"

class IExpressionFactory {
public:
    virtual ~IExpressionFactory() {}
    virtual IExpression * build(IExpression *, IExpression *) const = 0;
    virtual int getPriority() const = 0;
};

#endif