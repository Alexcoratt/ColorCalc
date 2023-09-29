#ifndef DIVISION_EXPRESSION_HPP
#define DIVISION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class DivisionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    DivisionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}

    std::vector<double> exec() {
        return std::vector<double>(1, _left->exec()[0] / _right->exec()[0]);
    }
};

#endif