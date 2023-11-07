#ifndef INT_VALUE_HPP
#define INT_VALUE_HPP

#include "IValue.hpp"

class IntValue : public IValue {
private:
	int _value;

public:
	IntValue(int);
	IntValue(IntValue const &);
	IntValue & operator=(IntValue const &);
	~IntValue();
	void swap(IntValue &);

	IntValue * operator=(IValue const *);
	void setValue(IValue const *);
	void const * getValue() const;
	IntValue * getClone() const;

	bool less(IValue const *) const;

	std::string toString() const;
	double toDouble() const;
	int toInt() const;
};

#endif
