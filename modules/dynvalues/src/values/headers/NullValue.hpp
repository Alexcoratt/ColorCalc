#ifndef NULL_VALUE_HPP
#define NULL_VALUE_HPP

#include "IValue.hpp"

class NullValue : public IValue {
public:
	NullValue * getClone() const;

	NullValue & operator=(IValue const &);

	bool operator<(IValue const &) const;

	operator std::string() const;
	operator double() const;
	operator int() const;
	operator unsigned long() const;

	bool isNull() const;
};

#endif
