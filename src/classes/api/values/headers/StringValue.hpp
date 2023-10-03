#ifndef STRING_VALUE_HPP
#define STRING_VALUE_HPP

#include <string>
#include "IValue.hpp"

class StringValue : public IValue {
private:
    std::string _value;

protected:
    inline std::string getErrorMessage() const { return "This is a string value. It cannot contain value of another type"; }

public:
    StringValue(std::string const & = "");
    StringValue(StringValue const &);
    StringValue & operator=(StringValue const &);
    ~StringValue();

    void swap(StringValue &);

    std::string getStringValue() const;
    void setStringValue(std::string const &);

    void print(std::ostream & = std::cout, std::string const & = "\n") const;
};

#endif