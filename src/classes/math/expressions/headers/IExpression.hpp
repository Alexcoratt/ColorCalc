#ifndef I_EXPRESSION_HPP
#define I_EXPRESSION_HPP

#include "IValue.hpp"

class IExpression {
public:
    virtual ~IExpression() {};

    virtual IValue * exec() = 0;
};

#endif
