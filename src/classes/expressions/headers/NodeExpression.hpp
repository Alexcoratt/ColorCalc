#ifndef NODE_EXPRESSION_HPP
#define NODE_EXPRESSION_HPP

#include "IExpression.hpp"
#include "IOperator.hpp"

class NodeExpression : public IExpression {
private:
    IOperator * _operator;
    std::vector<IExpression *> _expressions;

public:
    NodeExpression(IOperator * oper, std::vector<IExpression *> expressions) : _operator(oper), _expressions(expressions) {}

    double calculate() { return _operator->execute(_expressions); }
};

#endif
