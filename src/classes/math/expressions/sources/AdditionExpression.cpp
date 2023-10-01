#include <algorithm>
#include <vector>

#include "AdditionExpression.hpp"
#include "ExpressionException.hpp"

AdditionExpression::AdditionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {
    if (!_right)
        throw ExpressionException("Addition error: no right operand provided");
}

AdditionExpression::AdditionExpression(AdditionExpression const & other) : _left(other._left), _right(other._right) {}

AdditionExpression & AdditionExpression::operator=(AdditionExpression const & other) {
    if (&other != this) {
        AdditionExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

AdditionExpression::~AdditionExpression() {
    delete _left;
    delete _right;
}

std::vector<double> AdditionExpression::exec() {
    return std::vector<double>(1, (_left ? _left->exec()[0] : 0) + _right->exec()[0]);
}

void AdditionExpression::swap(AdditionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}