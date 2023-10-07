#include <algorithm>

#include "DoubleValue.hpp"
#include "RemoveVariableFunction.hpp"

RemoveVariableFunction::RemoveVariableFunction(Environment * env, IValue * var) : _env(env), _var(var) {}
RemoveVariableFunction::RemoveVariableFunction(RemoveVariableFunction const & other) : _env(other._env), _var(other._var) {}

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
    std::swap(_var, other._var);
}

IValue * RemoveVariableFunction::exec() {
    _env->removeVariable(_var);
    //std::cout << "hi from RemoveVariable" << std::endl;
    return new DoubleValue;
}
