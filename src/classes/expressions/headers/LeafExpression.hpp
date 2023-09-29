#ifndef LEAF_EXPRESSION_HPP
#define LEAF_EXPRESSION_HPP

#include <vector>
#include "IExpression.hpp"

class LeafExpression : public IExpression {
private:
    double _value;

public:
    LeafExpression(double value);
    LeafExpression(LeafExpression const &);
    LeafExpression & operator=(LeafExpression const &);
    ~LeafExpression();

    std::vector<double> exec();

    void swap(LeafExpression &);
};

#endif
