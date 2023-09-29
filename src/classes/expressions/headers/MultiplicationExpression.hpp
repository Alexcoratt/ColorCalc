#ifndef MULTIPLICATION_EXPRESSION_HPP
#define MULTIPLICATION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class MultiplicationExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    MultiplicationExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}
    ~MultiplicationExpression() {
        delete _left;
        delete _right;
    }

    std::vector<double> exec() {
        return std::vector<double>(1, _left->exec()[0] * _right->exec()[0]);
    }
};

#endif