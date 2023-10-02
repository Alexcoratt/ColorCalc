#include "LeafExpression.hpp"
#include <algorithm>
#include <vector>

LeafExpression::LeafExpression(DoubleValue * value, bool isVariable) : _value(value), _isVariable(isVariable) {}
LeafExpression::LeafExpression(LeafExpression const & other) : _value(other._value), _isVariable(other._isVariable) {}

LeafExpression & LeafExpression::operator=(LeafExpression const & other) {
    if (this != &other) {
        LeafExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

LeafExpression::~LeafExpression() {
    if (!_isVariable)
        delete _value;
}

std::vector<double> LeafExpression::exec() {
    return std::vector<double>(1, _value->getDoubleValue());
}

void LeafExpression::swap(LeafExpression & other) {
    std::swap(_value, other._value);
    std::swap(_isVariable, other._isVariable);
}