#include <algorithm>
#include <vector>

#include "SubtractionExpression.hpp"
#include "ExpressionException.hpp"

SubtractionExpression::SubtractionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {
    if (!_right)
        throw ExpressionException("Subtraction error: no right operand provided");
}

SubtractionExpression::SubtractionExpression(SubtractionExpression const & other) : _left(other._left), _right(other._right) {}

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

std::vector<double> SubtractionExpression::exec() {
    return std::vector<double>(1, (_left ? _left->exec()[0] : 0) - _right->exec()[0]);
}

void SubtractionExpression::swap(SubtractionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}
