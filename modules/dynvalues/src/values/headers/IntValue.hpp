#ifndef INT_VALUE_HPP
#define INT_VALUE_HPP

#include "IValue.hpp"

class IntValue : public IValue {
private:
	int _value;

public:
	IntValue(int);
	IntValue(IValue const &);
	IntValue & operator=(IValue const &);
	~IntValue();

	void swap(IntValue &);

	IntValue * getClone() const;

	bool operator<(IValue const &) const;

	operator std::string() const;
	operator double() const;
	operator int() const;
	operator unsigned long() const;
};

#endif
