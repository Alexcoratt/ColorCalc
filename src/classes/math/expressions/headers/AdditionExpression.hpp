#ifndef ADDITION_EXPRESSION_HPP
#define ADDITION_EXPRESSION_HPP

#include "IExpression.hpp"
#include "DoubleValue.hpp"

class AdditionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;
    DoubleValue * _result;

public:
    AdditionExpression(IExpression *, IExpression *);
    AdditionExpression(AdditionExpression const &);
    AdditionExpression & operator=(AdditionExpression const &);
    ~AdditionExpression();

    DoubleValue * exec();

    void swap(AdditionExpression &);
};

#endif