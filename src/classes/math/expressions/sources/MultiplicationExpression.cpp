#include <algorithm>
#include <string>

#include "MultiplicationExpression.hpp"
#include "ExpressionException.hpp"

MultiplicationExpression::MultiplicationExpression(IExpression * left, IExpression * right) : _left(left), _right(right), _result(new DoubleValue) {
    if (!_left || !_right)
        throw ExpressionException("Multiplication error: only two operands allowed, provided: " + std::to_string(_left == 0 + _right == 0));
}
MultiplicationExpression::MultiplicationExpression(MultiplicationExpression const & other) : _left(other._left), _right(other._right), _result(other._result) {}

MultiplicationExpression & MultiplicationExpression::operator=(MultiplicationExpression const & other) {
    if (this != &other) {
        MultiplicationExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

MultiplicationExpression::~MultiplicationExpression() {
    delete _left;
    delete _right;
    delete _result;
}

DoubleValue * MultiplicationExpression::exec() {
    _result->setDoubleValue(_left->exec()->getDoubleValue() * _right->exec()->getDoubleValue());
    return _result;
}

void MultiplicationExpression::swap(MultiplicationExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
    std::swap(_result, other._result);
}