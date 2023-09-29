#include "LeafExpression.hpp"
#include <algorithm>
#include <vector>

LeafExpression::LeafExpression(double value) : _value(value) {}
LeafExpression::LeafExpression(LeafExpression const & other) : _value(other._value) {}

LeafExpression & LeafExpression::operator=(LeafExpression const & other) {
    if (this != &other) {
        LeafExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

LeafExpression::~LeafExpression() {}

std::vector<double> LeafExpression::exec() {
    return std::vector<double>(1, _value);
}

void LeafExpression::swap(LeafExpression & other) {
    std::swap(_value, other._value);
}