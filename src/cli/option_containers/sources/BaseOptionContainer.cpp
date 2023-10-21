#include "BaseOptionContainer.hpp"
#include "BackOption.hpp"
#include "HelpOption.hpp"
#include "IOption.hpp"
#include "OptionAlreadyExistsException.hpp"
#include "OptionBackException.hpp"
#include "OptionDoesNotExistException.hpp"
#include "OptionQuitException.hpp"
#include "QuitOption.hpp"
#include <stdexcept>

BaseOptionContainer::BaseOptionContainer(std::map<char, IOption *> const & commands, std::string const & name, std::string const & help) : _options(commands), _name(name), _help(help) {}

BaseOptionContainer::BaseOptionContainer(std::string const & name, std::string const & help, bool noBackOption) {
	_name = name;
	_help = help;

	_options['h'] = new HelpOption;
	_options['h']->setNoDelete(false);

	_options['q'] = new QuitOption;
	_options['q']->setNoDelete(false);

	if (!noBackOption) {
		_options['b'] = new BackOption;
		_options['b']->setNoDelete(false);
	}
}

BaseOptionContainer::~BaseOptionContainer() {
	for (auto option : _options)
		if (!option.second->getNoDelete())
			delete option.second;
}

void BaseOptionContainer::exec(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) {
	output << "Switch to " << getName() << endline << endline;
	char option;
	while (input.get(option))
		try {
			if (option != '\n') {
				getOption(option)->exec(this, input, output, endline);
				output << endline;
			}
		} catch (OptionQuitException const * quit) {
			if (parent)
				throw quit;
			delete quit;
			break;
		} catch (OptionBackException const * back) {
			delete back;
			if (parent) {
				output << "Switch to " << parent->getName() << endline << endline;
				break;
			}
		} catch (std::exception const * err) {
			std::cerr << err->what() << std::endl;
		}

	if (!parent)
		output << "Goodbye" << endline;
	else if (input.eof())
		throw new OptionQuitException;
}

IOption * BaseOptionContainer::getOption(char name) {
	if (_options.find(name) != _options.end())
		return _options[name];
	throw new OptionDoesNotExistException(name);
}

void BaseOptionContainer::addOption(char name, IOption * option) {
	if (_options.find(name) != _options.end())
		throw new OptionAlreadyExistsException(name);
	_options[name] = option;
}

void BaseOptionContainer::removeOption(char name) {
	if (_options.find(name) == _options.end())
		throw new OptionDoesNotExistException(name);
	delete _options[name];
	_options.erase(name);
}
