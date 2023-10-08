#include "ValueExpression.hpp"
#include <algorithm>

ValueExpression::ValueExpression(IValue * value) : _value(value) {}
ValueExpression::ValueExpression(ValueExpression const & other) : _value(other._value) {}

ValueExpression & ValueExpression::operator=(ValueExpression const & other) {
    if (this != &other) {
        ValueExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

ValueExpression::~ValueExpression() {
    delete _value;
}

void ValueExpression::swap(ValueExpression & other) {
    std::swap(_value, other._value);
}

IValue * ValueExpression::exec() {
    return _value;
}
