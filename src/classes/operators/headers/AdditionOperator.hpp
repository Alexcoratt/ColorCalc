#ifndef PLUS_OPERATOR_HPP
#define PLUS_OPERATOR_HPP

#include "AbstractOperator.hpp"

class AdditionOperator : public AbstractOperator 
{
public:
    AdditionOperator() 
    {
        _basePriority = 0;
    }

    double execute(std::vector<IExpression *> expressions) 
    {
        double res = 0;
        for (std::size_t i = 0; i < expressions.size(); ++i)
            res += expressions[i]->calculate();
        return res;
    }
};

#endif
