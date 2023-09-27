#ifndef I_EXPRESSION_FACTORY_HPP
#define I_EXPRESSION_FACTORY_HPP

#include <vector>
#include "IExpression.hpp"

class IExpressionFactory {
public:
    virtual IExpression * build(IExpression *, IExpression * = 0) const = 0;

    /*
        Types of expressions:
            0: both unary and binary
            1: unary
            2: binary
    */
    virtual int getType() const = 0;
};

#endif