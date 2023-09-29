#ifndef SUBTRACTION_EXPRESSION_HPP
#define SUBTRACTION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class SubtractionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    SubtractionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}
    ~SubtractionExpression() {
        delete _left;
        delete _right;
    }

    std::vector<double> exec() {
        double left = _left ? _left->exec()[0] : 0;
        double right = _right ? _right->exec()[0] : 0;
        return std::vector<double>(1, left - right);
    }
};

#endif