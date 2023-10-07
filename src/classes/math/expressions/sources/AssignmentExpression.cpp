#include <algorithm>
#include <iostream>

#include "AssignmentExpression.hpp"

#include "IValue.hpp"

AssignmentExpression::AssignmentExpression(std::string const & varName, IExpression * right, Environment * env) : _varName(varName), _right(right), _env(env) {}
AssignmentExpression::AssignmentExpression(AssignmentExpression const & other) : _varName(other._varName), _right(other._right), _env(other._env), _result(other._result) {}

AssignmentExpression & AssignmentExpression::operator=(AssignmentExpression const & other) {
    if (this != &other) {
        AssignmentExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

AssignmentExpression::~AssignmentExpression() {
    delete _right;
    if (_result)
        delete _result;
}

void AssignmentExpression::swap(AssignmentExpression & other) {
    std::swap(_varName, other._varName);
    std::swap(_right, other._right);
    std::swap(_env, other._env);
    std::swap(_result, other._result);
}

IValue * AssignmentExpression::exec() {
    _result =_right->exec();
    _env->setVariable(_varName, _result);
    
    return _result;
}
