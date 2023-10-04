#include <algorithm>
#include "HelpCommandFactory.hpp"

HelpCommandFactory::HelpCommandFactory(std::map<std::string, ICommandFactory *> const * commands) : _commands(commands) {}
HelpCommandFactory::HelpCommandFactory(HelpCommandFactory const & other) : _commands(other._commands) {}

HelpCommandFactory & HelpCommandFactory::operator=(HelpCommandFactory const & other) {
    if (this != &other) {
        HelpCommandFactory tmp(other);
        swap(tmp);
    }
    return *this;
}

HelpCommandFactory::~HelpCommandFactory() {};

void HelpCommandFactory::swap(HelpCommandFactory & other) {
    std::swap(_commands, other._commands);
}

HelpCommand * HelpCommandFactory::build(std::map<std::string, std::string> const & args) {
    return new HelpCommand(_commands, args);
}

std::string HelpCommandFactory::getHelp() const {
    return "Some help";
}

std::string HelpCommandFactory::getFullHelp() const {
    return "Full help";
}
