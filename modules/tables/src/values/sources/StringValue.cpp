#include <algorithm>
#include <stdexcept>

#include "StringValue.hpp"

StringValue::StringValue(std::string const & value) : _value(value) {}
StringValue::StringValue(StringValue const & other) : _value(other._value) {}
StringValue & StringValue::operator=(StringValue const & other) {
	if (this != &other) {
		StringValue tmp(other);
		swap(tmp);
	}
	return *this;
}
StringValue::~StringValue() {}

void StringValue::swap(StringValue & other) { std::swap(_value, other._value); }

StringValue * StringValue::operator=(IValue const * other) {
	setValue(other);
	return this;
}

void StringValue::setValue(IValue const * other) { _value = other->toString(); }
void const * StringValue::getValue() const { return &_value; }

StringValue * StringValue::getClone() const { return new StringValue(_value); }

bool StringValue::less(IValue const * other) const { return _value < other->toString(); }

std::string StringValue::toString() const { return _value; }
double StringValue::toDouble() const { return std::stod(_value); }
int StringValue::toInt() const { return std::stoi(_value); }
