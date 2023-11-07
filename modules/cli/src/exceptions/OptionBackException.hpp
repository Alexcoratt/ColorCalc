#ifndef OPTION_BACK_EXCEPTION
#define OPTION_BACK_EXCEPTION

#include "CliException.hpp"

class OptionBackException : public CliException {
public:
	char const * what() const noexcept {
		return "CLI back exception";
	}
};

#endif
