#ifndef DIVISION_EXPRESSION_HPP
#define DIVISION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class DivisionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    DivisionExpression(IExpression *, IExpression *);
    DivisionExpression(DivisionExpression const &);
    DivisionExpression & operator=(DivisionExpression const &);
    ~DivisionExpression();

    std::vector<double> exec();

    void swap(DivisionExpression &);
};

#endif