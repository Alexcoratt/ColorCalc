#ifndef STRING_VALUE_HPP
#define STRING_VALUE_HPP

#include "IValue.hpp"

class StringValue : public IValue {
private:
	std::string _value;

public:
	StringValue(std::string const &);
	StringValue(StringValue const &);
	StringValue & operator=(StringValue const &);
	~StringValue();
	void swap(StringValue &);

	StringValue * operator=(IValue const *);
	void setValue(IValue const *);
	void const * getValue() const;

	bool less(IValue const *) const;

	std::string toString() const;
	double toDouble() const;
	int toInt() const;
};

#endif
