#include <algorithm>
#include <ostream>
#include "CommandParser.hpp"

#include "ICommand.hpp"

#include "HelpCommandFactory.hpp"

CommandParser::CommandParser(Environment * env) : _env(env) {
    _commands["help"] = new HelpCommandFactory(&_commands);
}

CommandParser::CommandParser(CommandParser const & other) : _commands(other._commands) {}

CommandParser & CommandParser::operator=(CommandParser const & other) {
    if (this != &other) {
        CommandParser tmp(other);
        swap(tmp);
    }
    return *this;
}

CommandParser::~CommandParser() {
    for (auto iter = _commands.begin(); iter != _commands.end(); ++iter) 
        delete iter->second;
}

void CommandParser::swap(CommandParser & other) {
    std::swap(_env, other._env);
    std::swap(_commands, other._commands);
}

void CommandParser::parseString(std::string prompt) {
    std::map<std::string, std::string> args;
    ICommand * cmd = _commands["help"]->build(args);
    cmd->exec(std::cout);
}