#include "NullValue.hpp"

NullValue * NullValue::getClone() const { return new NullValue; }

NullValue & NullValue::operator=(IValue const &) { return *this; }

bool NullValue::operator<(IValue const & other) const {
	if (other.isNull())
		return false;
	return true;
}

NullValue::operator std::string() const { return ""; }
NullValue::operator double() const { return 0; }
NullValue::operator int() const { return 0; }
NullValue::operator unsigned long() const { return 0; }

bool NullValue::isNull() const { return true; }
