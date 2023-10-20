#ifndef BACK_OPTION_HPP
#define BACK_OPTION_HPP

#include "AbstractLeafOption.hpp"
#include "OptionBackException.hpp"

class BackOption : public AbstractLeafOption {
	void exec(IOption *, std::istream &, std::ostream &, std::string const &) {
		throw new OptionBackException;
	}

	std::string getName() const { return "back"; }

	std::string getHelp() const { return getName() + ": Allows user to go to previous option list"; }
};

#endif
