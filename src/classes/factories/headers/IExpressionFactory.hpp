#ifndef I_EXPRESSION_FACTORY_HPP
#define I_EXPRESSION_FACTORY_HPP

#include <vector>
#include "IExpression.hpp"

class IExpressionFactory {
public:
    virtual IExpression * build(IExpression * = 0, IExpression * = 0) const = 0;
    virtual int getPriority() const = 0;
};

#endif