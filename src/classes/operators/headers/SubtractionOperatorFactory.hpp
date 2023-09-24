#ifndef SUBTRACTION_OPERATOR_FACTORY_HPP
#define SUBTRACTION_OPERATOR_FACTORY_HPP

#include "AbstractOperatorFactory.hpp"
#include "SubtractionOperator.hpp"

class SubtractionOperatorFactory : public AbstractOperatorFactory
{
public:
    AbstractOperator * build() const { return new SubtractionOperator; }
};


#endif