#ifndef I_EXPRESSION_HPP
#define I_EXPRESSION_HPP

#include <vector>

class IExpression {
public:
    virtual std::vector<double> exec() = 0;
};

#endif
