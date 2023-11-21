#ifndef LACQUER_DATA_DISPATCHER_HPP
#define LACQUER_DATA_DISPATCHER_HPP

#include "IConnection.hpp"
#include "AbstractDataDispatcher.hpp"

class LacquerDataDispatcher : public AbstractDataDispatcher {
public:
	LacquerDataDispatcher(IConnection *);

	double getPercentage() const;
	void setPercentage(double);

	double getLacquerConsumption() const;
	void setLacquerConsumption(double);

	double getSheetLength() const;
	void setSheetLength(double);

	double getSheetWidth() const;
	void setSheetWidth(double);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t);

	double calculate() const;
};

#endif
