#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP

#include "IExpression.hpp"
#include "Environment.hpp"
#include "IValue.hpp"

class AssignmentExpression : public IExpression {
private:
    std::string _varName;
    IExpression * _right;
    Environment * _env;
    IValue * _result;

public:
    AssignmentExpression(std::string const &, IExpression *, Environment *);
    AssignmentExpression(AssignmentExpression const &);
    AssignmentExpression & operator=(AssignmentExpression const &);
    ~AssignmentExpression();

    void swap(AssignmentExpression &);

    IValue * exec();
};

#endif
