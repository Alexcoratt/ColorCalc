#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include <string>

#include "IValue.hpp"

class Environment {
private:
    std::map<std::string, IValue *> _variables;

public:
    Environment();
    Environment(Environment const &);
    Environment & operator=(Environment const &);
    ~Environment();

    void swap(Environment &);

    IValue * getValue(std::string const &);

    bool containsVariable(std::string const &) const;
    void setVariable(std::string const &, IValue *);

    void removeVariable(std::string const &);
    void removeVariable(IValue *);
};

#endif