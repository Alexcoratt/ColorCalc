#ifndef PRIORITY_MODIFIER_HPP
#define PRIORITY_MODIFIER_HPP

class PriorityModifier
{
private:
    int _value;

public:
    PriorityModifier(int value) : _value(value) {}

    int getModified(int basePriority) const { return basePriority + _value; }
};

#endif