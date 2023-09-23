#ifndef CALCULATION_OPERATOR_HPP
#define CALCULATION_OPERATOR_HPP

#include <queue>
#include "PriorityModifier.hpp"
#include "IExpression.hpp"

class AbstractOperator
{
protected:
    int _basePriority;
    std::queue<PriorityModifier const *> _mods;

public:
    AbstractOperator() : _basePriority(0) {}

    virtual void addPriorityModifier(PriorityModifier const * mod) 
    {
        _mods.push(mod);
    }

    virtual int getPriority() 
    {
        int res = _basePriority;
        PriorityModifier const * startMod = _mods.front();
        _mods.pop();
        _mods.push(startMod);
        res = startMod->getModified(res);
        PriorityModifier const * mod = _mods.front();
        
        while (mod != startMod) {
            _mods.pop();
            _mods.push(mod);
            res = mod->getModified(res);
            mod = _mods.front();
        }

        return res;
    }

    virtual double execute(std::vector<IExpression *>) = 0;
};


#endif