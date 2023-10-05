#include <algorithm>
#include "RemoveVariableFunction.hpp"

RemoveVariableFunction::RemoveVariableFunction(Environment * env, std::string const & varName) : _env(env), _varName(varName) {}
RemoveVariableFunction::RemoveVariableFunction(RemoveVariableFunction const & other) : _env(other._env), _varName(other._varName) {}

RemoveVariableFunction & RemoveVariableFunction::operator=(RemoveVariableFunction const & other) {
    if (this != &other) {
        RemoveVariableFunction tmp(other);
        swap(tmp);
    }
    return *this;
}

RemoveVariableFunction::~RemoveVariableFunction() {}

void RemoveVariableFunction::swap(RemoveVariableFunction & other) {
    std::swap(_env, other._env);
    std::swap(_varName, other._varName);
}

IValue * RemoveVariableFunction::exec() {
    _env->removeVariable(_varName);
    return nullptr;
}