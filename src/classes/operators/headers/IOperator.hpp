#ifndef I_OPERATOR_HPP
#define I_OPERATOR_HPP

#include "IExpression.hpp"

class IOperator {
public:
    virtual double execute(std::vector<IExpression *>) = 0;
};

#endif
