#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include <map>
#include <string>
#include <vector>

#include "ICommand.hpp"
#include "ICommandFactory.hpp"

class HelpCommand : public ICommand {
private:
    std::map<std::string, ICommandFactory *> _commands;
    std::map<std::string, std::string> _args;

public:
    HelpCommand(std::map<std::string, ICommandFactory *>, std::map<std::string, std::string>);
    HelpCommand(HelpCommand const &);
    HelpCommand & operator=(HelpCommand const &);
    ~HelpCommand();

    void swap(HelpCommand &);

    void exec();
};

#endif