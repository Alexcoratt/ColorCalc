#ifndef DIVISION_EXPRESSION_HPP
#define DIVISION_EXPRESSION_HPP

#include "IExpression.hpp"
#include "DoubleValue.hpp"

class DivisionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;
    DoubleValue * _result;

public:
    DivisionExpression(IExpression *, IExpression *);
    DivisionExpression(DivisionExpression const &);
    DivisionExpression & operator=(DivisionExpression const &);
    ~DivisionExpression();

    DoubleValue * exec();

    void swap(DivisionExpression &);
};

#endif