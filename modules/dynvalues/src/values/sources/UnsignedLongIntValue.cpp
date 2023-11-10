#include "UnsignedLongIntValue.hpp"

UnsignedLongIntValue::UnsignedLongIntValue(unsigned long value) : _value(value) {}
UnsignedLongIntValue::UnsignedLongIntValue(UnsignedLongIntValue const & other) : _value(other._value) {}

UnsignedLongIntValue & UnsignedLongIntValue::operator=(IValue const & other) {
	_value = other;
	return *this;
}

UnsignedLongIntValue::~UnsignedLongIntValue() {}

UnsignedLongIntValue * UnsignedLongIntValue::getClone() const { return new UnsignedLongIntValue(_value); }

bool UnsignedLongIntValue::operator<(IValue const & other) const { return _value < (unsigned long)other; }

UnsignedLongIntValue::operator std::string() const { return std::to_string(_value); }
UnsignedLongIntValue::operator double() const { return _value; }
UnsignedLongIntValue::operator int() const { return _value; }
UnsignedLongIntValue::operator unsigned long() const { return _value; }
