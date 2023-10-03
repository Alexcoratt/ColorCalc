#ifndef SUBTRACTION_EXPRESSION_HPP
#define SUBTRACTION_EXPRESSION_HPP

#include "IExpression.hpp"
#include "DoubleValue.hpp"

class SubtractionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;
    DoubleValue * _result;

public:
    SubtractionExpression(IExpression *, IExpression *);
    SubtractionExpression(SubtractionExpression const &);
    SubtractionExpression & operator=(SubtractionExpression const &);
    ~SubtractionExpression();

    DoubleValue * exec();
    
    void swap(SubtractionExpression &);
};

#endif