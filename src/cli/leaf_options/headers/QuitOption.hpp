#ifndef QUIT_OPTION_HPP
#define QUIT_OPTION_HPP

#include "AbstractLeafOption.hpp"
#include "IOption.hpp"
#include "OptionQuitException.hpp"

class QuitOption : public AbstractLeafOption {
public:
	void exec(IOption *, std::istream &, std::ostream &, std::string const &) {
		throw new OptionQuitException;
	}

	std::string getName() const { return "quit"; }

	std::string getHelp() const { return "Ends the program"; }
};

#endif
