#ifndef I_OPTION_HPP
#define I_OPTION_HPP

#include <iostream>
#include <map>
#include <string>

class IOption {

public:
	virtual ~IOption() {}

	virtual void exec(IOption *, std::istream &, std::ostream &, std::string const &) = 0;
	virtual std::map<char, IOption *> getCommands() const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getHelp() const = 0;
};

#endif
