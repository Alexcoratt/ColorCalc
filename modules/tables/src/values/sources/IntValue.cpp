#include <algorithm>

#include "IntValue.hpp"

IntValue::IntValue(int value) : _value(value) {}
IntValue::IntValue(IntValue const & other) :_value(other._value) {}

IntValue & IntValue::operator=(IntValue const & other) {
	if (this != &other) {
		IntValue tmp(other);
		swap(tmp);
	}
	return *this;
}

IntValue::~IntValue() {}
void IntValue::swap(IntValue & other) { std::swap(_value, other._value); }

IntValue * IntValue::operator=(IValue const * other) {
	setValue(other);
	return this;
}

void IntValue::setValue(IValue const * other) { _value = other->toInt(); }
void const * IntValue::getValue() const { return &_value; }

bool IntValue::less(IValue const * other) const { return _value < other->toInt(); }

std::string IntValue::toString() const { return std::to_string(_value); }
double IntValue::toDouble() const { return double(_value); }
int IntValue::toInt() const { return _value; }
