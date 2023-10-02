#ifndef LEAF_EXPRESSION_FACTORY_HPP
#define LEAF_EXPRESSION_FACTORY_HPP

#include <string>

#include "IExpressionFactory.hpp"
#include "LeafExpression.hpp"
#include "Environment.hpp"

class LeafExpressionFactory : public IExpressionFactory {
private:
    double _value;

public:
    LeafExpressionFactory(Environment *, std::string const &);
    LeafExpressionFactory(LeafExpressionFactory const &);
    LeafExpressionFactory & operator=(LeafExpressionFactory const &);
    ~LeafExpressionFactory();

    void swap(LeafExpressionFactory &);

    LeafExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif