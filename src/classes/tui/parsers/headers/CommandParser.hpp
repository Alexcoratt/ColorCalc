#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <map>
#include <string>

#include "ICommandFactory.hpp"
#include "Environment.hpp"

class CommandParser {
private:
    Environment * _env;
    std::map<std::string, ICommandFactory *> _commands;

public:
    CommandParser(Environment *);
    CommandParser(CommandParser const &);
    CommandParser & operator=(CommandParser const &);
    ~CommandParser();

    void swap(CommandParser &);

    std::string parseString(std::string);
};

#endif