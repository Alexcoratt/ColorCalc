#ifndef CALCULATION_OPERATOR_HPP
#define CALCULATION_OPERATOR_HPP

#include <vector>
#include "PriorityModifier.hpp"

class CalculationOperator
{
private:
    int _basePriority;
    std::vector<PriorityModifier*> _mods;

public:
    CalculationOperator() : _basePriority(0) {}

    virtual void setBasePriority(int basePriority) { _basePriority = basePriority; }

    virtual int getPriority() 
    {
        int res = _basePriority;
        for (PriorityModifier const * mod : _mods)
            res = mod->getModified(res);

        return res;
    }
};


#endif