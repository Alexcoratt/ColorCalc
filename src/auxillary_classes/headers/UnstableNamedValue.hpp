#ifndef UNSTABLE_NAMED_VALUE_HPP
#define UNSTABLE_NAMED_VALUE_HPP

#include <string>

#include "UndefinedValueException.hpp"

template <typename T>
class UnstableNamedValue {
private:
	T _value;
	std::string _name;
	bool _defined;

public:
	UnstableNamedValue() {
		_name = "unnamed";
		_defined = false;
	}

	UnstableNamedValue(T const & value, std::string name = "unnamed", bool defined = true) : _value(value), _name(name), _defined(defined) {}


	T getValue() const {
		if (!_defined)
			throw UndefinedValueException(_name);
		return _value;
	}

	operator T() const { return getValue(); }

	void setValue(T const & value) {
		_value = value;
		_defined = true;
	}

	UnstableNamedValue & operator=(T const & value) {
		setValue(value);
		return *this;
	}

	bool operator==(T const & value) const { return _value == value; }

	std::string getName() const { return _name; }
	void setName(std::string const & name) { _name = name; }

	bool isDefined() const { return _defined; }
	void clear() { _defined = false; }
};

#endif
