#ifndef REMOVE_VARIABLE_FUNCTION_HPP
#define REMOVE_VARIABLE_FUNCTION_HPP

#include <string>

#include "IFunction.hpp"
#include "Environment.hpp"

class RemoveVariableFunction : public IFunction {
private:
    Environment * _env;
    std::string _varName;

public:
    RemoveVariableFunction(Environment *, std::string const &);
    RemoveVariableFunction(RemoveVariableFunction const &);
    RemoveVariableFunction & operator=(RemoveVariableFunction const &);
    ~RemoveVariableFunction();

    void swap(RemoveVariableFunction &);

    IValue * exec();
};

#endif