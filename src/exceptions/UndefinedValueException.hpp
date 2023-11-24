#ifndef UNDEFINED_VALUE_EXCEPTION_HPP
#define UNDEFINED_VALUE_EXCEPTION_HPP

#include <exception>
#include <string>

class UndefinedValueException : public std::exception {
private:
	std::string _msg;

public:
	inline UndefinedValueException(std::string const & name) :
		_msg("Value named \"" + name + "\" is undefined")
	{}

	inline char const * what() const noexcept { return _msg.c_str(); }
};

#endif
