#ifndef AUTO_VALUE_HPP
#define AUTO_VALUE_HPP

#include "IValue.hpp"

class AutoValue : public IValue {
private:
	IValue * _value;

public:
	AutoValue();
	AutoValue(IValue const &);
	AutoValue(double);
	AutoValue(int);
	AutoValue(std::string const &);
	AutoValue(char const *);
	~AutoValue();

	int nestCount() const;

	AutoValue & operator=(AutoValue const &);
	AutoValue & operator=(IValue const &);

	void swap(AutoValue &);

	AutoValue * getClone() const;

	bool operator<(IValue const &) const;

	operator std::string() const;
	operator double() const;
	operator int() const;

	bool isNull() const;
};

#endif
