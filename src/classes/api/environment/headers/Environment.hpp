#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include <string>

class Environment {
private:
    std::map<std::string, std::string> * _variables;

public:
    std::string getVariable(std::string const &) const;
    std::string & getVariableLink(std::string const &);

    bool containsVariable(std::string const &) const;
    void setVariable(std::string const &, std::string const &);
};

#endif