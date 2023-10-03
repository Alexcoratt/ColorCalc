#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP

#include "IExpression.hpp"
#include "LeafExpression.hpp"
#include "DoubleValue.hpp"
#include "Environment.hpp"

class AssignmentExpression : public IExpression {
private:
    LeafExpression * _left;
    IExpression * _right;
    Environment * _env;
    DoubleValue * _result;

public:
    AssignmentExpression(LeafExpression *, IExpression *, Environment *);
    AssignmentExpression(AssignmentExpression const &);
    AssignmentExpression & operator=(AssignmentExpression const &);
    ~AssignmentExpression();

    void swap(AssignmentExpression &);

    DoubleValue * exec();
};

#endif