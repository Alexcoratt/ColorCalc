#include <algorithm>

#include "DoubleValue.hpp"

DoubleValue::DoubleValue(double value) : _value(value) {}
DoubleValue::DoubleValue(IValue const & other) : _value(other) {}

DoubleValue & DoubleValue::operator=(IValue const & other) {
	if (this != &other) {
		DoubleValue tmp(other);
		swap(tmp);
	}
	return *this;
}

DoubleValue::~DoubleValue() {}
void DoubleValue::swap(DoubleValue & other) { std::swap(_value, other._value); }

DoubleValue * DoubleValue::getClone() const { return new DoubleValue(_value); }

bool DoubleValue::operator<(IValue const & other) const { return _value < double(other); }

DoubleValue::operator std::string() const { return std::to_string(_value); }
DoubleValue::operator double() const { return _value; }
DoubleValue::operator int() const { return _value; }
DoubleValue::operator unsigned long() const { return _value; }
