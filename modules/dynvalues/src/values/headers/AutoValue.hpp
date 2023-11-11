#ifndef AUTO_VALUE_HPP
#define AUTO_VALUE_HPP

#include "IValue.hpp"
#include "SmartPointer.hpp"

class AutoValue : public IValue {
private:
	SmartPointer<IValue> _value;

public:
	AutoValue();
	AutoValue(AutoValue const &);
	AutoValue(IValue const &);
	AutoValue(double);
	AutoValue(int);
	AutoValue(unsigned long);
	AutoValue(std::string const &);
	AutoValue(char const *);
	~AutoValue();

	int nestCount() const;
	void clear();

	AutoValue & operator=(AutoValue const &);
	AutoValue & operator=(IValue const &);

	void swap(AutoValue &);

	AutoValue * getClone() const;

	bool operator<(IValue const &) const;

	operator std::string() const;
	operator double() const;
	operator int() const;
	operator unsigned long() const;

	bool isNull() const;
};

#endif
