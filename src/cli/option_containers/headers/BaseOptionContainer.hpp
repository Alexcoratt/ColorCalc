#ifndef CONTAINER_SIMPLE_COMMAND_HPP
#define CONTAINER_SIMPLE_COMMAND_HPP

#include "IOption.hpp"

#define BASE_NAME "base option container"
#define BASE_HELP_TEXT "base option container"

class BaseOptionContainer : public IOption {
protected:
	std::map<char, IOption *> _options;
	std::string _name;
	std::string _help;

public:
	BaseOptionContainer(std::map<char, IOption *> const &, std::string const & = BASE_NAME, std::string const & = BASE_HELP_TEXT);
	BaseOptionContainer(std::string const & = BASE_NAME, std::string const & = BASE_HELP_TEXT, bool = false);

	~BaseOptionContainer();

	void exec(IOption *, std::istream &, std::ostream &, std::string const &);
	std::map<char, IOption *> getCommands() const { return _options; }

	std::string getName() const { return _name; }
	std::string getHelp() const { return _name + ": " + _help; }

	IOption * getOption(char);
	void addOption(char, IOption *);
	void removeOption(char);
};

#endif
