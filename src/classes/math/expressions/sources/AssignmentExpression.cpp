#include <algorithm>
#include <iostream>

#include "AssignmentExpression.hpp"

#include "IValue.hpp"
#include "VariableExpression.hpp"

AssignmentExpression::AssignmentExpression(VariableExpression * var, IExpression * right) : _var(var), _right(right) {}
AssignmentExpression::AssignmentExpression(AssignmentExpression const & other) : _var(other._var), _right(other._right) {}

AssignmentExpression & AssignmentExpression::operator=(AssignmentExpression const & other) {
    if (this != &other) {
        AssignmentExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

AssignmentExpression::~AssignmentExpression() {
    delete _right;
}

void AssignmentExpression::swap(AssignmentExpression & other) {
    std::swap(_var, other._var);
    std::swap(_right, other._right);
}

IValue * AssignmentExpression::exec() {
    _var->setValue(_right->exec()->getClone());
    return _var->exec();
}
