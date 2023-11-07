#ifndef CONTAINER_SIMPLE_COMMAND_HPP
#define CONTAINER_SIMPLE_COMMAND_HPP

#include "IOption.hpp"

#define BASE_NAME "base option container"
#define BASE_HELP_TEXT "contains other options and containers"

class BaseOptionContainer : public IOption {
protected:
	std::string _name;
	std::string _help;
	std::map<char, IOption *> _options;

public:
	BaseOptionContainer(std::string const & = BASE_NAME, std::string const & = BASE_HELP_TEXT, std::map<char, IOption *> const & = {}, bool = false);

	~BaseOptionContainer();

	void exec(IOption *, std::istream &, std::ostream &, std::string const &);
	std::map<char, IOption *> getOptions() const { return _options; }

	std::string getName() const { return _name; }
	std::string getHelp() const { return _help; }

	IOption * getOption(char) const;
	void addOption(char, IOption *);
	void addOption(std::pair<char, IOption *> const &);
	void removeOption(char);
};

#endif
