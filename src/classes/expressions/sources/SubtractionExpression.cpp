#include "SubtractionExpression.hpp"
#include <algorithm>
#include <vector>

SubtractionExpression::SubtractionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}
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
    double left = _left ? _left->exec()[0] : 0;
    double right = _right ? _right->exec()[0] : 0;
    return std::vector<double>(1, left - right);
}

void SubtractionExpression::swap(SubtractionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}
