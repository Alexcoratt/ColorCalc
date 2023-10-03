#include <algorithm>

#include "AssignmentExpressionFactory.hpp"
#include "ExpressionException.hpp"

AssignmentExpressionFactory::AssignmentExpressionFactory(Environment * env) : _env(env) {}
AssignmentExpressionFactory::AssignmentExpressionFactory(AssignmentExpressionFactory const & other) : _env(other._env) {}

AssignmentExpressionFactory & AssignmentExpressionFactory::operator=(AssignmentExpressionFactory const & other) {
    if (this != &other) {
        AssignmentExpressionFactory tmp(other);
        swap(tmp);
    }
    return *this;
}

AssignmentExpressionFactory::~AssignmentExpressionFactory() {}

void AssignmentExpressionFactory::swap(AssignmentExpressionFactory & other) {
    std::swap(_env, other._env);
}

IExpression * AssignmentExpressionFactory::build(IExpression * left, IExpression * right) const {
    LeafExpression * var = dynamic_cast<LeafExpression *>(left);

    if (!var)
        throw ExpressionException("Expression exception: left operand must be a variable");

    return new AssignmentExpression(var, right, _env);
}

int AssignmentExpressionFactory::getPriority() const { return 0; }