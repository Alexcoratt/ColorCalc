#include "AdditionExpression.hpp"
#include <algorithm>
#include <vector>

AdditionExpression::AdditionExpression(IExpression * left, IExpression * right) : _left(left), _right(right) {}
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
    double left = _left ? _left->exec()[0] : 0;
    double right = _right ? _right->exec()[0] : 0;
    return std::vector<double>(1, left + right);
}

void AdditionExpression::swap(AdditionExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
}