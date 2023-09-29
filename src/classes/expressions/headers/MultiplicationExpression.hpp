#ifndef MULTIPLICATION_EXPRESSION_HPP
#define MULTIPLICATION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class MultiplicationExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    MultiplicationExpression(IExpression *, IExpression *);
    MultiplicationExpression(MultiplicationExpression const &);
    MultiplicationExpression & operator=(MultiplicationExpression const &);
    ~MultiplicationExpression();

    std::vector<double> exec();

    void swap(MultiplicationExpression &);
};

#endif