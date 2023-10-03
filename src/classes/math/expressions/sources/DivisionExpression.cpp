#include <algorithm>
#include <string>

#include "DivisionExpression.hpp"
#include "ExpressionException.hpp"

DivisionExpression::DivisionExpression(IExpression * left, IExpression * right) : _left(left), _right(right), _result(new DoubleValue) {
    if (!_left || !_right)
        throw ExpressionException("Division error: only two operands allowed, provided: " + std::to_string(_left == 0 + _right == 0));
}

DivisionExpression::DivisionExpression(DivisionExpression const & other) : _left(other._left), _right(other._right), _result(other._result) {}

DivisionExpression & DivisionExpression::operator=(DivisionExpression const & other) {
    if (this != &other) {
        DivisionExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

DivisionExpression::~DivisionExpression() {
    delete _left;
    delete _right;
    delete _result;
}

DoubleValue * DivisionExpression::exec() {
    _result->setDoubleValue(_left->exec()->getDoubleValue() / _right->exec()->getDoubleValue());
    return _result;
}

void DivisionExpression::swap(DivisionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
    std::swap(_result, other._result);
}