#ifndef LEAF_EXPRESSION_HPP
#define LEAF_EXPRESSION_HPP

#include "IExpression.hpp"

class LeafExpression : public IExpression {
private:
    double _value;

public:
    LeafExpression(double value) : _value(value) {}

    double calculate() { return _value; }
};

#endif
