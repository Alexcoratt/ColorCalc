#ifndef ASSIGNMENT_EXPRESSION_FACTORY_HPP
#define ASSIGNMENT_EXPRESSION_FACTORY_HPP

#include "IExpressionFactory.hpp"
#include "AssignmentExpression.hpp"
#include "Environment.hpp"

class AssignmentExpressionFactory : public IExpressionFactory {
private:
    Environment * _env;

public:
    AssignmentExpressionFactory(Environment *);
    AssignmentExpressionFactory(AssignmentExpressionFactory const &);
    AssignmentExpressionFactory & operator=(AssignmentExpressionFactory const &);
    ~AssignmentExpressionFactory();

    void swap(AssignmentExpressionFactory &);

    IExpression * build(IExpression *, IExpression *) const;

    int getPriority() const;
};

#endif