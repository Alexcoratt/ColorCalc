#ifndef ADDITION_OPERATOR_FACTORY_HPP
#define ADDITION_OPERATOR_FACTORY_HPP

#include "AbstractOperatorFactory.hpp"
#include "AdditionOperator.hpp"

class AdditionOperatorFactory : public AbstractOperatorFactory
{
    AbstractOperator * build() const { return new AdditionOperator; }
};

#endif