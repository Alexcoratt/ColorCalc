#include <algorithm>
#include <stdexcept>

#include "StringValue.hpp"

StringValue::StringValue(std::string const & value) : _value(value) {}
StringValue::StringValue(char const * value) : _value(value) {}
StringValue::StringValue(IValue const & other) : _value(other) {}
StringValue & StringValue::operator=(IValue const & other) {
	if (this != &other) {
		StringValue tmp(other);
		swap(tmp);
	}
	return *this;
}
StringValue::~StringValue() {}

void StringValue::swap(StringValue & other) { std::swap(_value, other._value); }

StringValue * StringValue::getClone() const { return new StringValue(_value); }

bool StringValue::operator<(IValue const & other) const { return _value < std::string(other); }

StringValue::operator std::string() const { return _value; }

StringValue::operator double() const {
	throw std::invalid_argument("operator double(): string value cannot be represented as value of type double");
}

StringValue::operator int() const {
	throw std::invalid_argument("operator int(): string value cannot be represented as value of type int");
}

StringValue::operator unsigned long() const {
	throw std::invalid_argument("operator unsigned long(): string value cannot be represented as value of type unsigned long");
}
