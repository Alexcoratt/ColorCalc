#ifndef REMOVE_VARIABLE_FUNCTION_HPP
#define REMOVE_VARIABLE_FUNCTION_HPP

#include <string>

#include "Environment.hpp"
#include "IExpression.hpp"

class RemoveVariableFunction : public IExpression {
private:
    Environment * _env;
    IValue * _var;

public:
    RemoveVariableFunction(Environment *, IValue *);
    RemoveVariableFunction(RemoveVariableFunction const &);
    RemoveVariableFunction & operator=(RemoveVariableFunction const &);
    ~RemoveVariableFunction();

    void swap(RemoveVariableFunction &);

    IValue * exec();
};

#endif