#ifndef OPTION_ALREADY_EXISTS_EXCEPTION
#define OPTION_ALREADY_EXISTS_EXCEPTION

#include "CliException.hpp"
#include <string>

class OptionAlreadyExistsException : public CliException {
private:
	std::string _msg;

public:
	OptionAlreadyExistsException(char option) {
		_msg = "Option \'" + std::string(1, option) + "\' already exists";
	}

	char const * what() const noexcept {
		return _msg.c_str();
	}
};

#endif
