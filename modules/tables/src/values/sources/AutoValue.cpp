#include <algorithm>

#include "AutoValue.hpp"
#include "DoubleValue.hpp"
#include "IntValue.hpp"
#include "StringValue.hpp"

AutoValue::AutoValue() : _value(new IntValue(0)) {}
AutoValue::AutoValue(IValue * value) : _value(value) {}
AutoValue::AutoValue(IValue const * value) : _value(value->getClone()) {}
AutoValue::AutoValue(double value) : _value(new DoubleValue(value)) {}
AutoValue::AutoValue(int value) : _value(new IntValue(value)) {}
AutoValue::AutoValue(std::string const & value) : _value(new StringValue(value)) {}
AutoValue::AutoValue(char const * value) : _value(new StringValue(value)) {}

AutoValue::AutoValue(AutoValue const & other) : _value(other._value) {}
AutoValue & AutoValue::operator=(AutoValue const & other) {
	if (this != &other) {
		AutoValue tmp(other);
		swap(tmp);
	}
	return *this;
}

AutoValue::~AutoValue() {}

void AutoValue::swap(AutoValue & other) { std::swap(_value, other._value); }

AutoValue * AutoValue::operator=(IValue const * other) {
	setValue(other);
	return this;
}

void AutoValue::setValue(IValue const * other) {
	if (this != other)
		_value->setValue(other);
}

void const * AutoValue::getValue() const { return _value->getValue(); }
AutoValue * AutoValue::getClone() const { return new AutoValue(*this); }
bool AutoValue::less(IValue const * other) const { return _value->less(other); }

std::string AutoValue::toString() const { return _value->toString(); }
double AutoValue::toDouble() const { return _value->toDouble(); }
int AutoValue::toInt() const { return _value->toInt(); }
