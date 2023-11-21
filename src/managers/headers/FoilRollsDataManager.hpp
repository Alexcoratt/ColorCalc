#ifndef FOIL_ROLLS_DATA_DISPATCHER_HPP
#define FOIL_ROLLS_DATA_DISPATCHER_HPP

#include <AbstractDataDispatcher.hpp>

class FoilRollsDataDispatcher : public AbstractDataDispatcher {
public:
	FoilRollsDataDispatcher(IConnection *);

	double calculate() const;

	double getLength() const;
	void setLength(double);

	double getWidth() const;
	void setWidth(double);
};

#endif
