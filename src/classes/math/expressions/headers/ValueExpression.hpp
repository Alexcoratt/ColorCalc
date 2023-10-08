#ifndef VALUE_EXPRESSION_HPP
#define VALUE_EXPRESSION_HPP

#include "IExpression.hpp"

class ValueExpression : public IExpression {
private:
    IValue * _value;

public:
    ValueExpression(IValue * value);
    ValueExpression(ValueExpression const &);
    ValueExpression & operator=(ValueExpression const &);
    ~ValueExpression();

    void swap(ValueExpression &);

    IValue * exec();
};

#endif
