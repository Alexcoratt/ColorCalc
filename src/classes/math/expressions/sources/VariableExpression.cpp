#include "VariableExpression.hpp"
#include "Environment.hpp"
#include "IValue.hpp"
#include <algorithm>

VariableExpression::VariableExpression(std::string const & name, Environment * env) : _name(name), _env(env) {}

VariableExpression::VariableExpression(VariableExpression const & other) : _name(other._name) {}

VariableExpression & VariableExpression::operator=(VariableExpression const & other) {
    if (this != &other) {
        VariableExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

VariableExpression::~VariableExpression() {}

void VariableExpression::swap(VariableExpression & other) {
    std::swap(_name, other._name);
    std::swap(_env, other._env);
}

IValue * VariableExpression::exec() {
    return _env->getValue(_name);
}

void VariableExpression::setValue(IValue * value) {
    _env->setVariable(_name, value);
}

std::string VariableExpression::getName() const {
    return _name;
}
