#include <algorithm>

#include "RemoveVariableFunction.hpp"
#include "VoidValue.hpp"

RemoveVariableFunction::RemoveVariableFunction(Environment * env, std::string const & varName) : _env(env), _varName(varName), _result(new VoidValue) {}
RemoveVariableFunction::RemoveVariableFunction(RemoveVariableFunction const & other) : _env(other._env), _varName(other._varName), _result(other._result) {}

RemoveVariableFunction & RemoveVariableFunction::operator=(RemoveVariableFunction const & other) {
    if (this != &other) {
        RemoveVariableFunction tmp(other);
        swap(tmp);
    }
    return *this;
}

RemoveVariableFunction::~RemoveVariableFunction() {
    delete _result;
}

void RemoveVariableFunction::swap(RemoveVariableFunction & other) {
    std::swap(_env, other._env);
    std::swap(_varName, other._varName);
    std::swap(_result, other._result);
}

IValue * RemoveVariableFunction::exec() {
    _env->removeVariable(_varName);
    return _result;
}
