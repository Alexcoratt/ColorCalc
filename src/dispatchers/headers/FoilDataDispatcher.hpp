#ifndef FOIL_DATA_DISPATCHER_HPP
#define FOIL_DATA_DISPATCHER_HPP

#include "AbstractDataDispatcher.hpp"
#include "IConnection.hpp"

class FoilDataDispatcher : public AbstractDataDispatcher {
public:
	FoilDataDispatcher(IConnection *);

	double calculate() const;

	std::size_t getCirculation() const;
	void setCirculation(std::size_t const &);

	double getLength() const;
	void setLength(double);

	double getWidth() const;
	void setWidth(double);

	std::size_t getSheetNumber() const;
	void setSheetNumber(std::size_t const &);

	double getLengthReserve() const;
	void setLengthReserve(double);

	double getWidthReserve() const;
	void setWidthReserve(double);

	std::vector<std::string> getSuitableFoilRolls() const;
};

#endif
