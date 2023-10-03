#include <algorithm>

#include "AssignmentExpression.hpp"

#include "ValueException.hpp"
#include "ExpressionException.hpp"

AssignmentExpression::AssignmentExpression(LeafExpression * left, IExpression * right, Environment * env) : _left(left), _right(right), _env(env), _result(new DoubleValue) {}
AssignmentExpression::AssignmentExpression(AssignmentExpression const & other) : _left(other._left), _right(other._right), _env(other._env), _result(other._result) {}

AssignmentExpression & AssignmentExpression::operator=(AssignmentExpression const & other) {
    if (this != &other) {
        AssignmentExpression tmp(other);
        swap(tmp);
    }
    return *this;
}

AssignmentExpression::~AssignmentExpression() {
    delete _left;
    delete _right;
    delete _result;
}

void AssignmentExpression::swap(AssignmentExpression & other) {
    std::swap(_left, other._left);
    std::swap(_right, other._right);
    std::swap(_env, other._env);
    std::swap(_result, other._result);
}

DoubleValue * AssignmentExpression::exec() {
    _result->setDoubleValue(_right->exec()->getDoubleValue());

    if (_left->getIsVariable())
        _left->exec()->setDoubleValue(_result->getDoubleValue());
    else {
        try {
            _env->setVariable(_left->exec()->getStringValue(), new DoubleValue(*_result));
        } catch (ValueException & err) {
            throw ExpressionException("Expression exception: left operand must be a variable");
        }
    }
    
    return _result;
}
