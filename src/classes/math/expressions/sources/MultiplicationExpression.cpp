#include <algorithm>
#include <vector>
#include <string>

#include "MultiplicationExpression.hpp"
#include "ExpressionException.hpp"

MultiplicationExpression::MultiplicationExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {
    if (!_left || !_right) {
        std::string errMsg = "Multiplication error: only two operands allowed, provided: " + std::to_string(_left == 0 + _right == 0);
        throw ExpressionException(errMsg.c_str());
    }
}
MultiplicationExpression::MultiplicationExpression(MultiplicationExpression const & other) : _left(other._left), _right(other._right) {}

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
}

std::vector<double> MultiplicationExpression::exec() {
    return std::vector<double>(1, _left->exec()[0] * _right->exec()[0]);
}

void MultiplicationExpression::swap(MultiplicationExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}