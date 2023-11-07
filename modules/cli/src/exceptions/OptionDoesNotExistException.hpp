#ifndef OPTION_DOES_NOT_EXIST_EXCEPTION
#define OPTION_DOES_NOT_EXIST_EXCEPTION

#include "CliException.hpp"
#include <string>

class OptionDoesNotExistException : public CliException {
private:
	std::string _msg;

public:
	OptionDoesNotExistException(char option) {
		_msg = "Option \'" + std::string(1, option) + "\' does not exist";
	}

	char const * what() const noexcept {
		return _msg.c_str();
	}
};

#endif
