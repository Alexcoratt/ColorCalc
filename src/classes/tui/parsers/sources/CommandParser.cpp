#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>

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

std::vector<std::string> split(std::string const & line, std::string const & delimiter = " ") {
    std::vector<std::string> res;
    std::size_t len = line.size();
    std::size_t delimLen = delimiter.size();
    std::size_t lastPos = 0;

    for (std::size_t pos = 0; pos < len; ++pos) {
        std::size_t distance = 0;

        while (line[pos + distance] == delimiter[distance] && pos + distance < len && distance < delimLen)
            ++distance;

        if (line.substr(pos, distance) == delimiter) {
            if (pos > lastPos)
                res.push_back(line.substr(lastPos, pos - lastPos));
            pos += distance - 1;
            lastPos = pos + 1;
        }
    }

    if (lastPos < len)
        res.push_back(line.substr(lastPos));

    return res;
}

void CommandParser::parseString(std::string prompt) {
    std::vector<std::string> lexems = split(prompt);
    for (std::string lexem : lexems)
        std::cout << '\"' << lexem << '\"' << std::endl;

    std::string commandName = lexems[0];
    std::size_t lexemCount = lexems.size();

    std::map<char, std::string> flags;
    std::map<std::string, std::string> params;
    std::vector<std::string> args;

    for (std::size_t i = 1; i < lexemCount; ++i) {
        std::string const & lexem = lexems[i];
        if (lexem[0] == '-') {
            if (lexem.size() < 2)
                throw std::invalid_argument("Wrong flag definition");

            if (lexem[1] == '-') {
                if (lexem.size() < 3)
                    throw std::invalid_argument("Wrong parameter definition");
                std::vector<std::string> keyVal = split(lexem.substr(2), "=");
                params[keyVal[0]] = keyVal.size() > 1 ? keyVal[1] : "";
            } else {
                for (char flag : lexem.substr(1))
                    flags[flag] = "";
                if (i + 1 < lexemCount && lexems[i + 1][0] != '-')
                    flags[lexem[lexem.size() - 1]] = lexems[++i];
            }
        } else {
            args.push_back(lexem);
        }
    }

    std::cout << std::endl << "Flags" << std::endl;
    for (auto iter = flags.begin(); iter != flags.end(); ++iter)
        std::cout << iter->first << ": \"" << iter->second << '\"' << std::endl;

    std::cout << std::endl << "Parameters" << std::endl;
    for (auto iter = params.begin(); iter != params.end(); ++iter)
        std::cout << iter->first << ": \"" << iter->second << '\"' << std::endl;

    std::cout << std::endl << "Arguments" << std::endl;
    for (std::string iter : args)
        std::cout << '\"' << iter << '\"' << std::endl;

    std::cout << std::endl;
}