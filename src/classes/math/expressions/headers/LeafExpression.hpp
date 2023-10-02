#ifndef LEAF_EXPRESSION_HPP
#define LEAF_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"
#include "DoubleValue.hpp"

class LeafExpression : public IExpression {
private:
    DoubleValue * _value;
    bool _isVariable;

public:
    LeafExpression(DoubleValue * value, bool isVariable);
    LeafExpression(LeafExpression const &);
    LeafExpression & operator=(LeafExpression const &);
    ~LeafExpression();

    std::vector<double> exec();

    void swap(LeafExpression &);
};

#endif
