#ifndef JSON_VALUE_IS_NULL_EXCEPTION_HPP
#define JSON_VALUE_IS_NULL_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class JsonValueIsNullException : public std::invalid_argument {
public:
	JsonValueIsNullException(std::string const & key) : std::invalid_argument("Json map contains null under \"" + key + "\" key") {}
};

#endif
