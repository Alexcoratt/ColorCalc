#ifndef SUBTRACTION_EXPRESSION_HPP
#define SUBTRACTION_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class SubtractionExpression : public IExpression {
private:
    IExpression * _left;
    IExpression * _right;

public:
    SubtractionExpression(IExpression *, IExpression *);
    SubtractionExpression(SubtractionExpression const &);
    SubtractionExpression & operator=(SubtractionExpression const &);
    ~SubtractionExpression();

    std::vector<double> exec();
    
    void swap(SubtractionExpression &);
};

#endif