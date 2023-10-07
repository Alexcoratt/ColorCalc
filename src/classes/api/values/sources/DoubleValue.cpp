#include <algorithm>
#include "DoubleValue.hpp"
#include "IValue.hpp"

DoubleValue::DoubleValue(double value) : _value(value) {}
DoubleValue::DoubleValue(DoubleValue const & other) : _value(other._value) {}

DoubleValue & DoubleValue::operator=(DoubleValue const & other) {
    if (this != &other) {
        DoubleValue tmp(other);
        swap(tmp);
    }
    return *this;
}

DoubleValue::~DoubleValue() {}

void DoubleValue::swap(DoubleValue & other) {
    std::swap(_value, other._value);
}

double DoubleValue::getDoubleValue() const { return _value; }
void DoubleValue::setDoubleValue(double value) { _value = value; }

void DoubleValue::print(std::ostream & out, std::string const & endline) const {
    out << getDoubleValue() << endline;
}

DoubleValue * DoubleValue::getClone() const { return new DoubleValue(*this); }
