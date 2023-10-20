#include "BaseOptionContainer.hpp"
#include "BackOption.hpp"
#include "HelpOption.hpp"
#include "IOption.hpp"
#include "OptionAlreadyExistsException.hpp"
#include "OptionBackException.hpp"
#include "OptionDoesNotExistException.hpp"
#include "OptionQuitException.hpp"
#include "QuitOption.hpp"
#include <cstdio>
#include <limits>
#include <stdexcept>

BaseOptionContainer::BaseOptionContainer(std::map<char, IOption *> const & commands, std::string const & name, std::string const & help) : _options(commands), _name(name), _help(help) {}

BaseOptionContainer::BaseOptionContainer(std::string const & name, std::string const & help, bool noBackOption) {
	_name = name;
	_help = help;

	_options['h'] = new HelpOption;
	_options['q'] = new QuitOption;

	if (!noBackOption)
		_options['b'] = new BackOption;
}

BaseOptionContainer::~BaseOptionContainer() {
	for (auto command : _options)
		delete command.second;
}

void BaseOptionContainer::exec(IOption * parent, std::istream & input, std::ostream & output, std::string const & endline) {
	output << getName() << endline;
	char option;
	while (input.get(option))
		try {
			if (option != '\n') {
				if (_options.find(option) != _options.end())
					_options[option]->exec(this, input, output, endline);
				else
					output << "Option \'" << option << "\' is not found" << endline;
				output << endline;
			}
		} catch (OptionQuitException const * quit) {
			if (parent)
				throw quit;
			delete quit;
			output << "Goodbye)" << endline;
			break;
		} catch (OptionBackException const * back) {
			delete back;
			if (parent) {
				output << parent->getName() << endline;
				break;
			}
		} catch (std::exception const * err) {
			std::cerr << err->what() << std::endl;
		}
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
