#include "DivisionExpression.hpp"
#include <algorithm>
#include <vector>

DivisionExpression::DivisionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}
DivisionExpression::DivisionExpression(DivisionExpression const & other) : _left(other._left), _right(other._right) {}

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
}

std::vector<double> DivisionExpression::exec() {
    return std::vector<double>(1, _left->exec()[0] / _right->exec()[0]);
}

void DivisionExpression::swap(DivisionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}