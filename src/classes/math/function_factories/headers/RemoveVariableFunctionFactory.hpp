#ifndef REMOVE_VARIABLE_FUNCTION_FACTORY_HPP
#define REMOVE_VARIABLE_FUNCTION_FACTORY_HPP

#include "IExpressionFactory.hpp"
#include "RemoveVariableFunction.hpp"

class RemoveVariableFunctionFactory : public IExpressionFactory {
private:
    Environment * _env;

public:
    RemoveVariableFunctionFactory(Environment *);
    RemoveVariableFunctionFactory(RemoveVariableFunctionFactory const &);
    RemoveVariableFunctionFactory & operator=(RemoveVariableFunctionFactory const &);
    ~RemoveVariableFunctionFactory();

    void swap(RemoveVariableFunctionFactory &);

    RemoveVariableFunction * build(IExpression *, IExpression *) const;

    inline int getPriority() const { return 4; };
};

#endif
