#ifndef VARIABLE_EXPRESSION_HPP
#define VARIABLE_EXPRESSION_HPP

#include "IExpression.hpp"
#include "IValue.hpp"
#include "Environment.hpp"

class VariableExpression : public IExpression {
private:
    std::string _name;
    Environment * _env;

public:
    VariableExpression(std::string const &, Environment *);
    VariableExpression(VariableExpression const &);
    VariableExpression & operator=(VariableExpression const &);
    ~VariableExpression();

    void swap(VariableExpression &);

    IValue * exec();

    void setValue(IValue *);

    std::string getName() const;
};

#endif
