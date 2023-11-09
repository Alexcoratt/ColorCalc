#ifndef NULL_VALUE_EXCEPTION_HPP
#define NULL_VALUE_EXCEPTION_HPP

#include <exception>

class NullValueException : std::exception {
public:
	inline char const * what() const noexcept { return "NullValue object cannot contain any value"; }
};

#endif
