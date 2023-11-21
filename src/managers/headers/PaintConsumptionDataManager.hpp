#ifndef PAINT_CONSUMPTION_DISPATHCHER_HPP
#define PAINT_CONSUMPTION_DISPATHCHER_HPP

#include "AbstractDataDispatcher.hpp"

class PaintConsumptionDispatcher : public AbstractDataDispatcher {
public:
	PaintConsumptionDispatcher(IConnection * paintConsumptionConnection);

	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getMaterialTypes() const;
	double getPaintConsumption(std::string const & paintType, std::string const & materialType) const;

	inline double calculate() const { throw std::runtime_error("PaintConsumptionDispatcher does no calculations"); }
};

#endif
