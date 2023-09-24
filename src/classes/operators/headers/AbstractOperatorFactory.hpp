#ifndef OPERATOR_FACTORY_HPP
#define OPERATOR_FACTORY_HPP

#include "AbstractOperator.hpp"

class AbstractOperatorFactory
{
public:
    virtual AbstractOperator * build() const = 0;
};

#endif