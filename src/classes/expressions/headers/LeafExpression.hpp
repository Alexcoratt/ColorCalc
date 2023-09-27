#ifndef LEAF_EXPRESSION_HPP
#define LEAF_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class LeafExpression : public IExpression {
private:
    double _value;

public:
    LeafExpression(double value) : _value(value) {}

    std::vector<double> calculate() { return std::vector<double>(_value); }
};

#endif
