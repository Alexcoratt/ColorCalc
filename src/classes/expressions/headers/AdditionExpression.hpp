#ifndef ADDITION_EXPRESSION_HPP
#define ADDITION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class AdditionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    AdditionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}

    std::vector<double> exec() {
        double left = _left ? _left->exec()[0] : 0;
        double right = _right ? _right->exec()[0] : 0;
        return std::vector<double>(left + right);
    }
};

#endif