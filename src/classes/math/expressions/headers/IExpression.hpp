#ifndef I_EXPRESSION_HPP
#define I_EXPRESSION_HPP

#include <vector>

class IExpression {
public:
    virtual ~IExpression() {};

    virtual std::vector<double> exec() = 0;
};

#endif
