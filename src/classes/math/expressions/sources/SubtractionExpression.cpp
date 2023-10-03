#include <algorithm>

#include "SubtractionExpression.hpp"
#include "ExpressionException.hpp"

SubtractionExpression::SubtractionExpression(IExpression * left, IExpression * right) : _left(left), _right(right), _result(new DoubleValue) {
    if (!_right)
        throw ExpressionException("Subtraction error: no right operand provided");
}

SubtractionExpression::SubtractionExpression(SubtractionExpression const & other) : _left(other._left), _right(other._right), _result(other._result) {}

SubtractionExpression & SubtractionExpression::operator=(SubtractionExpression const & other) {
    if (this != &other) {
        SubtractionExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

SubtractionExpression::~SubtractionExpression() {
    delete _left;
    delete _right;
}

DoubleValue * SubtractionExpression::exec() {
    _result->setDoubleValue((_left ? _left->exec()->getDoubleValue() : 0) - _right->exec()->getDoubleValue());
    return _result;
}

void SubtractionExpression::swap(SubtractionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}
