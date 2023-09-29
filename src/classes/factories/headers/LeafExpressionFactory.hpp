#ifndef LEAF_EXPRESSION_FACTORY_HPP
#define LEAF_EXPRESSION_FACTORY_HPP

#include "IExpressionFactory.hpp"
#include "LeafExpression.hpp"

class LeafExpressionFactory : public IExpressionFactory {
private:
    double _value;

public:
    LeafExpressionFactory(double value) : _value(value) {}

    IExpression * build(IExpression * first = 0, IExpression * second = 0) const {
        return new LeafExpression(_value);
    }

    int getPriority() const { return 5; }
};

#endif