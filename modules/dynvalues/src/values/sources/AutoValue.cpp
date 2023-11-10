#include <algorithm>

#include "AutoValue.hpp"
#include "DoubleValue.hpp"
#include "IntValue.hpp"
#include "UnsignedLongIntValue.hpp"
#include "StringValue.hpp"

AutoValue::AutoValue() : _value(new IntValue(0)) {}
AutoValue::AutoValue(IValue const & value) { _value = value.getClone(); }
AutoValue::AutoValue(double value) : _value(new DoubleValue(value)) {}
AutoValue::AutoValue(int value) : _value(new IntValue(value)) {}
AutoValue::AutoValue(unsigned long value) : _value(new UnsignedLongIntValue(value)) {}
AutoValue::AutoValue(std::string const & value) : _value(new StringValue(value)) {}
AutoValue::AutoValue(char const * value) : _value(new StringValue(value)) {}

AutoValue & AutoValue::operator=(AutoValue const & other) {
	if (this != &other) {
		AutoValue tmp(*other._value);
		swap(tmp);
	}
	return *this;
}

AutoValue & AutoValue::operator=(IValue const & other) {
	if (this != &other) {
		AutoValue tmp(other);
		swap(tmp);
	}
	return *this;
}

AutoValue::~AutoValue() { delete _value; }

int AutoValue::nestCount() const {
	AutoValue * value = dynamic_cast<AutoValue *>(_value);
	if (value)
		return 1 + value->nestCount();
	return 0;
}

void AutoValue::swap(AutoValue & other) { std::swap(_value, other._value); }

AutoValue * AutoValue::getClone() const { return new AutoValue(*_value); }
bool AutoValue::operator<(IValue const & other) const { return *_value < other; }

AutoValue::operator std::string() const { return *_value; }
AutoValue::operator double() const { return *_value; }
AutoValue::operator int() const { return *_value; }
AutoValue::operator unsigned long() const { return *_value; }

bool AutoValue::isNull() const { return _value->isNull(); }
