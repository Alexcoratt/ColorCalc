#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP

#include "IExpression.hpp"
#include "IValue.hpp"
#include "VariableExpression.hpp"

class AssignmentExpression : public IExpression {
private:
    VariableExpression * _var;
    IExpression * _right;

public:
    AssignmentExpression(VariableExpression *, IExpression *);
    AssignmentExpression(AssignmentExpression const &);
    AssignmentExpression & operator=(AssignmentExpression const &);
    ~AssignmentExpression();

    void swap(AssignmentExpression &);

    IValue * exec();
};

#endif
