#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include <string>

class Environment {
private:
    std::map<std::string, double> _variables;
    //std::map<std::string, ICommand> _commands;
};

#endif