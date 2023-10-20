#ifndef OPTION_QUIT_EXCEPTION
#define OPTION_QUIT_EXCEPTION

#include "CliException.hpp"

class OptionQuitException : public CliException {
public:
	char const * what() const noexcept {
		return "CLI quit exception";
	}
};

#endif
