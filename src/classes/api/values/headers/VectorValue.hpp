#ifndef VECTOR_VALUE_HPP
#define VECTOR_VALUE_HPP

#include "IValue.hpp"

class VectorValue : public IValue
{
private:
    std::vector<IValue *> _values;

protected:
    inline std::string getErrorMessage() const { return "This is a vector value. It cannot contain value of another type"; }

public:
    VectorValue(std::vector<IValue *> const &);
    VectorValue(VectorValue const &);
    VectorValue & operator=(VectorValue const &);
    ~VectorValue();

    void swap(VectorValue &);

    std::vector<IValue *> getVectorValue() const;
    void setVectorValue(std::vector<IValue *> const &);

    void print(std::ostream & = std::cout, std::string const & = "\n") const;

    VectorValue * getClone() const;
};


#endif
