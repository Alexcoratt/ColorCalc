#ifndef ADDITION_EXPRESSION_HPP
#define ADDITION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class AdditionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    AdditionExpression(IExpression *, IExpression *);
    AdditionExpression(AdditionExpression const &);
    AdditionExpression & operator=(AdditionExpression const &);
    ~AdditionExpression();

    std::vector<double> exec();

    void swap(AdditionExpression &);
};

#endif