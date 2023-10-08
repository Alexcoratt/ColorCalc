#ifndef REMOVE_VARIABLE_FUNCTION_HPP
#define REMOVE_VARIABLE_FUNCTION_HPP

#include <string>

#include "Environment.hpp"
#include "IExpression.hpp"
#include "IValue.hpp"

class RemoveVariableFunction : public IExpression {
private:
    Environment * _env;
    std::string _varName;
    IValue * _result;

public:
    RemoveVariableFunction(Environment *, std::string const &);
    RemoveVariableFunction(RemoveVariableFunction const &);
    RemoveVariableFunction & operator=(RemoveVariableFunction const &);
    ~RemoveVariableFunction();

    void swap(RemoveVariableFunction &);

    IValue * exec();
};

#endif
