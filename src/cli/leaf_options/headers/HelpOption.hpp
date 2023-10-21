#ifndef HELP_OPTION_HPP
#define HELP_OPTION_HPP

#include "IOption.hpp"
#include "IOption.hpp"

class HelpOption : public IOption {
public:
	void exec(IOption *, std::istream &, std::ostream &, std::string const &);
	std::string getName() const { return "help"; }
	std::string getHelp() const { return "Returns list of available commands"; }
};

#endif
