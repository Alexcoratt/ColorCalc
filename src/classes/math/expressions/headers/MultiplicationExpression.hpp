#ifndef MULTIPLICATION_EXPRESSION_HPP
#define MULTIPLICATION_EXPRESSION_HPP

#include "IExpression.hpp"
#include "DoubleValue.hpp"

class MultiplicationExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;
    DoubleValue * _result;

public:
    MultiplicationExpression(IExpression *, IExpression *);
    MultiplicationExpression(MultiplicationExpression const &);
    MultiplicationExpression & operator=(MultiplicationExpression const &);
    ~MultiplicationExpression();

    DoubleValue * exec();

    void swap(MultiplicationExpression &);
};

#endif