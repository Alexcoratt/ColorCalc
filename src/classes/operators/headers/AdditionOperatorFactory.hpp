#ifndef ADDITION_OPERATOR_FACTORY_HPP
#define ADDITION_OPERATOR_FACTORY_HPP

#include "IOperatorFactory.hpp"
#include "AdditionOperator.hpp"

class AdditionOperatorFactory : public IOperatorFactory
{
    AbstractOperator * build() const { return new AdditionOperator; }
};

#endif