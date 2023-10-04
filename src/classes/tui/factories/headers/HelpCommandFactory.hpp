#ifndef HELP_COMMAND_FACTORY_HPP
#define HELP_COMMAND_FACTORY_HPP

#include "ICommandFactory.hpp"
#include "HelpCommand.hpp"

class HelpCommandFactory : public ICommandFactory {
private:
    std::map<std::string, ICommandFactory *> const * _commands;

public:
    HelpCommandFactory(std::map<std::string, ICommandFactory *> const *);
    HelpCommandFactory(HelpCommandFactory const &);
    HelpCommandFactory & operator=(HelpCommandFactory const &);
    ~HelpCommandFactory();

    void swap(HelpCommandFactory &);

    HelpCommand * build(std::map<std::string, std::string> const &);

    std::string getHelp() const;
    std::string getFullHelp() const;
};

#endif