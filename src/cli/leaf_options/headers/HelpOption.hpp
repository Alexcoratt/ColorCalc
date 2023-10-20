#ifndef HELP_OPTION_HPP
#define HELP_OPTION_HPP

#include "AbstractLeafOption.hpp"
#include "IOption.hpp"

class HelpOption : public AbstractLeafOption {
public:
	void exec(IOption *, std::istream &, std::ostream &, std::string const &);

	std::string getName() const { return "help"; }

	std::string getHelp() const { return getName() + ": Returns list of available commands"; }
};

#endif
