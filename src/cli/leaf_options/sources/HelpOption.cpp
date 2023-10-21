#include "HelpOption.hpp"
#include "BaseOptionContainer.hpp"
#include <stdexcept>

void HelpOption::exec(IOption * parent, std::istream &, std::ostream & output, std::string const & endline) {
	BaseOptionContainer * parentContainer = dynamic_cast<BaseOptionContainer *>(parent);

	if (parentContainer) {
		output << "Available commands:" << endline;
		for (auto option : parentContainer->getOptions())
			output << option.first << "\t" << option.second->getName() << ": " << option.second->getHelp() << endline;
	} else {
		throw new std::invalid_argument("Parent must be pointer to a container");
	}
}
