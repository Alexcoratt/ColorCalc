#ifndef VOID_VALUE_HPP
#define VOID_VALUE_HPP

#include "IValue.hpp"
#include "ValueException.hpp"
#include <ostream>

class VoidValue : public IValue {
protected:
    inline std::string getErrorMessage() const { return "This is the void value. It cannot contain value of any type"; }

public:
    inline void print(std::ostream &, std::string const &) const {
        throw ValueException(getErrorMessage().c_str());
    }

    inline VoidValue * getClone() const { return new VoidValue; }
};

#endif
