#include <algorithm>

#include "DoubleValue.hpp"

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
void DoubleValue::swap(DoubleValue & other) { std::swap(_value, other._value); }

DoubleValue * DoubleValue::operator=(IValue const * other) {
	setValue(other);
	return this;
}

void DoubleValue::setValue(IValue const * other) { _value = other->toDouble(); }
void const * DoubleValue::getValue() const { return &_value; }

DoubleValue * DoubleValue::getClone() const { return new DoubleValue(_value); }

bool DoubleValue::less(IValue const * other) const { return _value < other->toDouble(); }

std::string DoubleValue::toString() const { return std::to_string(_value); }
double DoubleValue::toDouble() const { return _value; }
int DoubleValue::toInt() const { return int(_value); }
