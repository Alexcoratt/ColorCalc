#ifndef DEFAULT_OPTION_IS_CHOSEN_EXCEPTION_HPP
#define DEFAULT_OPTION_IS_CHOSEN_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class DefaultOptionIsChosenException : public std::exception {
public:
	char const * what() const noexcept {
		return "Default option is chosen";
	}
};

#endif
