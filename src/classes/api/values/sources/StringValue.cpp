#include <algorithm>
#include "StringValue.hpp"

StringValue::StringValue(std::string const & str) : _value(str) {}
StringValue::StringValue(StringValue const & other) : _value(other._value) {}

StringValue & StringValue::operator=(StringValue const & other) {
    if (this != &other) {
        StringValue tmp(other);
        swap(tmp);
    }
    return *this;
}

StringValue::~StringValue() {}

void StringValue::swap(StringValue & other) {
    std::swap(_value, other._value);
}

std::string StringValue::getStringValue() const { return _value; }
void StringValue::setStringValue(std::string const & str) { _value = str; }