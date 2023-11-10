#include <algorithm>

#include "IntValue.hpp"

IntValue::IntValue(int value) : _value(value) {}
IntValue::IntValue(IValue const & other) : _value(other) {}

IntValue & IntValue::operator=(IValue const & other) {
	if (this != &other) {
		IntValue tmp(other);
		swap(tmp);
	}
	return *this;
}

IntValue::~IntValue() {}
void IntValue::swap(IntValue & other) { std::swap(_value, other._value); }

IntValue * IntValue::getClone() const { return new IntValue(_value); }

bool IntValue::operator<(IValue const & other) const { return _value < int(other); }

IntValue::operator std::string() const { return std::to_string(_value); }
IntValue::operator double() const { return _value; }
IntValue::operator int() const { return _value; }
IntValue::operator unsigned long() const { return _value; }
