#include <algorithm>

#include "AdditionExpression.hpp"
#include "ExpressionException.hpp"

AdditionExpression::AdditionExpression(IExpression * left, IExpression * right) : _left(left), _right(right), _result(new DoubleValue) {
    if (!_right)
        throw ExpressionException("Addition error: no right operand provided");
}

AdditionExpression::AdditionExpression(AdditionExpression const & other) : _left(other._left), _right(other._right), _result(other._result) {}

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
    delete _result;
}

DoubleValue * AdditionExpression::exec() {
    _result->setDoubleValue((_left ? _left->exec()->getDoubleValue() : 0) + _right->exec()->getDoubleValue());
    return _result;
}

void AdditionExpression::swap(AdditionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
    std::swap(_result, other._result);
}