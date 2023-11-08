#ifndef I_VALUE_HPP
#define I_VALUE_HPP

#include <string>
#include <vector>
#include <map>

class IValue {
public:
	virtual ~IValue() {}

	virtual IValue * operator=(IValue const *) = 0;
	virtual void setValue(IValue const *) = 0;
	virtual void const * getValue() const = 0;
	virtual IValue * getClone() const = 0;

	virtual bool less(IValue const *) const = 0;

	virtual std::string toString() const = 0;
	virtual double toDouble() const = 0;
	virtual int toInt() const = 0;

	virtual inline operator std::string() const { return toString(); }
	virtual inline operator double() const { return toDouble(); }
	virtual inline operator int() const { return toInt(); }
};

#endif
