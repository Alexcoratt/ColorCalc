#include "LeafExpression.hpp"
#include <algorithm>

LeafExpression::LeafExpression(IValue * value, bool isVariable) : _value(value), _isVariable(isVariable) {}
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

void LeafExpression::swap(LeafExpression & other) {
    std::swap(_value, other._value);
    std::swap(_isVariable, other._isVariable);
}

IValue * LeafExpression::exec() {
    return _value;
}

bool LeafExpression::getIsVariable() const { return _isVariable; }
void LeafExpression::setIsVariable(bool value) { _isVariable = value; }