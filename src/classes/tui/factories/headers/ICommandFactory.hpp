#ifndef I_COMMAND_FACTORY_HPP
#define I_COMMAND_FACTORY_HPP

#include <map>
#include <string>

#include "ICommand.hpp"
#include "Environment.hpp"

class ICommandFactory
{
public:
    virtual ICommand * build(std::map<std::string, std::string> const &) = 0;
    
    virtual std::string getHelp() const = 0;
    virtual std::string getFullHelp() const = 0;
};

#endif