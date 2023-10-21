#include "BaseOptionContainer.hpp"
#include "BackOption.hpp"
#include "CliException.hpp"
#include "HelpOption.hpp"
#include "IOption.hpp"
#include "OptionAlreadyExistsException.hpp"
#include "OptionBackException.hpp"
#include "OptionDoesNotExistException.hpp"
#include "OptionQuitException.hpp"
#include "QuitOption.hpp"
#include <stdexcept>

BaseOptionContainer::BaseOptionContainer(std::string const & name, std::string const & help, std::map<char, IOption *> const & options, bool noBackOption) : _name(name), _help(help) {
	_options['h'] = new HelpOption;
	_options['h']->setNoDelete(false);

	_options['q'] = new QuitOption;
	_options['q']->setNoDelete(false);

	if (!noBackOption) {
		_options['b'] = new BackOption;
		_options['b']->setNoDelete(false);
	}

	for (auto option : options)
		addOption(option);
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
			output << "\"" << getName() << "\" is the root container" << endline << endline;
		} catch (CliException * err) {
			output << err->what() << endline << endline;
			delete err;
		} catch (std::exception const * err) {
			std::cerr << err->what() << std::endl;
			delete err;
		}

	if (!parent)
		output << "Goodbye" << endline;
	else if (input.eof())
		throw new OptionQuitException;
}

IOption * BaseOptionContainer::getOption(char name) const {
	auto option = _options.find(name);
	if (option != _options.end())
		return option->second;
	throw new OptionDoesNotExistException(name);
}

void BaseOptionContainer::addOption(char name, IOption * option) {
	if (_options.find(name) != _options.end())
		throw new OptionAlreadyExistsException(name);
	_options[name] = option;
}

void BaseOptionContainer::addOption(std::pair<char, IOption *> const & option) {
	if (_options.find(option.first) != _options.end())
		throw new OptionAlreadyExistsException(option.first);
	_options.insert(option);
}

void BaseOptionContainer::removeOption(char name) {
	if (_options.find(name) == _options.end())
		throw new OptionDoesNotExistException(name);
	delete _options[name];
	_options.erase(name);
}
