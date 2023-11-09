#ifndef INCOMPATIBLE_VALUE_TYPES_EXCEPTION_HPP
#define INCOMPATIBLE_VALUE_TYPES_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

class IncompatibleValueTypesException : public std::exception {
private:
	std::string _msg;

public:
	inline IncompatibleValueTypesException(std::vector<std::string> const & typeNames) {
		unsigned long size = typeNames.size();
		if (size == 0)
			throw std::invalid_argument("no type names provided");
		if (size == 1)
			throw std::invalid_argument("only one type name provided");

		_msg = "Types " + typeNames[0];
		for (unsigned int i = 1; i < size - 1; ++i) {
			_msg.append(", ").append(typeNames[i]);
		}
		_msg.append(" and ").append(typeNames[size - 1]).append(" are incompatible");
	}

	inline char const * what() const noexcept { return _msg.c_str(); }
};

#endif
