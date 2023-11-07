#ifndef DOUBLE_VALUE_HPP
#define DOUBLE_VALUE_HPP

#include "IValue.hpp"

class DoubleValue : public IValue {
private:
	double _value;

public:
	DoubleValue(double);
	DoubleValue(DoubleValue const &);
	DoubleValue & operator=(DoubleValue const &);
	~DoubleValue();
	void swap(DoubleValue &);

	DoubleValue * operator=(IValue const *);
	void setValue(IValue const *);
	void const * getValue() const;

	bool less(IValue const *) const;

	std::string toString() const;
	double toDouble() const;
	int toInt() const;
};

#endif
