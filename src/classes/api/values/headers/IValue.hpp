#ifndef I_VALUE_HPP
#define I_VALUE_HPP

#include <string>
#include <vector>
#include <iostream>

#include "ValueException.hpp"

class IValue {
protected:
    virtual std::string getErrorMessage() const = 0;

public:
    virtual ~IValue() {}

    virtual std::string getStringValue() const { throw ValueException(getErrorMessage().c_str()); }
    virtual void setStringValue(std::string const &) { throw ValueException(getErrorMessage().c_str()); }

    virtual double getDoubleValue() const { throw ValueException(getErrorMessage().c_str()); }
    virtual void setDoubleValue(double) { throw ValueException(getErrorMessage().c_str()); }

    virtual std::vector<IValue *> getVectorValue() const { throw ValueException(getErrorMessage().c_str()); }
    virtual void setVectorValue(std::vector<IValue *> const &) { throw ValueException(getErrorMessage().c_str()); }

    virtual void print(std::ostream & = std::cout, std::string const & = "\n") const = 0;

    virtual IValue * getClone() const = 0;
};

#endif
