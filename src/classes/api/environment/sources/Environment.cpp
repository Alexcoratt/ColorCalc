#include <algorithm>

#include "Environment.hpp"
#include "VariableException.hpp"

Environment::Environment() {}
Environment::Environment(Environment const & other) : _variables(other._variables) {}

Environment & Environment::operator=(Environment const & other) {
    if (this != &other) {
        Environment tmp(other);
        swap(tmp);
    }
    return *this;
}

Environment::~Environment() {
    for (auto iter = _variables.begin(); iter != _variables.end(); ++iter)
        delete iter->second;
}

void Environment::swap(Environment & other) { std::swap(_variables, other._variables); }

IValue * Environment::getValue(std::string const & key) { 
    if (!containsVariable(key))
        throw VariableException("Variable named \"" + key + "\" does not exist");
    return _variables[key];
}

bool Environment::containsVariable(std::string const & key) const { return _variables.find(key) != _variables.end(); }
void Environment::setVariable(std::string const & key, IValue * value) { _variables[key] = value; }
void Environment::removeVariable(std::string const & key) { _variables.erase(key); }