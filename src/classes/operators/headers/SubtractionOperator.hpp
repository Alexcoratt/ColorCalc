#ifndef MINUS_OPERATOR_HPP
#define MINUS_OPERATOR_HPP

#include "AbstractOperator.hpp"

class SubtractionOperator : public AbstractOperator
{
public:
    SubtractionOperator()
    {
        _basePriority = 0;
    }

    double execute(std::vector<IExpression *> expressions)
    {
        double res = expressions[0]->calculate();
        for (std::size_t i = 1; i < expressions.size(); ++i)
            res -= expressions[i]->calculate();
        return res;
    }
};

#endif
