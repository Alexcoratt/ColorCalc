#ifndef AUTO_VALUE_HPP
#define AUTO_VALUE_HPP

#include "IValue.hpp"
#include "SmartPointer.hpp"

class AutoValue : public IValue {
private:
	SmartPointer<IValue> _value;

public:
	AutoValue();
	AutoValue(IValue *);
	AutoValue(IValue const *);
	AutoValue(double);
	AutoValue(int);
	AutoValue(std::string const &);
	AutoValue(char const *);

	AutoValue(AutoValue const &);
	AutoValue & operator=(AutoValue const &);
	~AutoValue();

	void swap(AutoValue &);

	AutoValue * operator=(IValue const *);
	void setValue(IValue const *);
	void const * getValue() const;
	AutoValue * getClone() const;

	bool less(IValue const *) const;

	std::string toString() const;
	double toDouble() const;
	int toInt() const;
};

#endif
