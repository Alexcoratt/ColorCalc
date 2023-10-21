#ifndef BACK_OPTION_HPP
#define BACK_OPTION_HPP

#include "IOption.hpp"
#include "OptionBackException.hpp"

class BackOption : public IOption {
	void exec(IOption *, std::istream &, std::ostream &, std::string const &) {
		throw new OptionBackException;
	}

	std::string getName() const { return "back"; }
	std::string getHelp() const { return "Allows user to go to previous option list"; }
};

#endif
