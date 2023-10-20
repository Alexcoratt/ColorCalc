#include "HelpOption.hpp"
#include <stdexcept>

void HelpOption::exec(IOption * parent, std::istream &, std::ostream & output, std::string const & endline) {
	auto parentCommands = parent->getCommands();
	output << "Available commands:" << endline;
	for (auto command : parentCommands)
		std::cout << command.first << "\t" << command.second->getHelp() << endline;
}
