#ifndef DOUBLE_VALUE_HPP
#define DOUBLE_VALUE_HPP

#include <string>
#include "IValue.hpp"

class DoubleValue : public IValue {
private:
    double _value;

protected:
    inline std::string getErrorMessage() const { return "This is a double value. It cannot contain value of another type"; }

public:
    DoubleValue(double = 0);
    DoubleValue(DoubleValue const &);
    DoubleValue & operator=(DoubleValue const &);
    ~DoubleValue();

    void swap(DoubleValue &);

    double getDoubleValue() const;
    void setDoubleValue(double);
};

#endif