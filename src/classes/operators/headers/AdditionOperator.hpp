#ifndef PLUS_OPERATOR_HPP
#define PLUS_OPERATOR_HPP

#include "IOperator.hpp"

class AdditionOperator : public IOperator {
public:
    double execute(std::vector<IExpression *> expressions) {
        double res = 0;
        for (std::size_t i = 0; i < expressions.size(); ++i)
            res += expressions[i]->calculate();
        return res;
    }
};

#endif
