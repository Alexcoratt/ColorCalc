#ifndef LEAF_EXPRESSION_HPP
#define LEAF_EXPRESSION_HPP

#include "IExpression.hpp"
#include "DoubleValue.hpp"

class LeafExpression : public IExpression {
private:
    IValue * _value;
    bool _isVariable;

public:
    LeafExpression(IValue * value, bool isVariable);
    LeafExpression(LeafExpression const &);
    LeafExpression & operator=(LeafExpression const &);
    ~LeafExpression();

    void swap(LeafExpression &);

    IValue * exec();

    bool getIsVariable() const;
    void setIsVariable(bool);
};

#endif
