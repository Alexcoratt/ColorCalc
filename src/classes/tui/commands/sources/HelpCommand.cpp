#include "algorithm"
#include "HelpCommand.hpp"

HelpCommand::HelpCommand(std::map<std::string, ICommandFactory *> commands, std::map<std::string, std::string> args) : _commands(commands), _args(args) {}
HelpCommand::HelpCommand(HelpCommand const & other) : _commands(other._commands), _args(other._args) {}

HelpCommand & HelpCommand::operator=(HelpCommand const & other) {
    if (this != &other) {
        HelpCommand tmp(other);
        swap(tmp);
    }
    return *this;
}

HelpCommand::~HelpCommand() {}

void HelpCommand::swap(HelpCommand & other) {
    std::swap(_commands, other._commands);
    std::swap(_args, other._args);
}

void HelpCommand::exec() {}