#ifndef PAINT_CONSUMPTION_DATA_MANAGER_HPP
#define PAINT_CONSUMPTION_DATA_MANAGER_HPP

#include "IDataManager.hpp"

class PaintConsumptionDataManager : public IDataManager {
public:
	PaintConsumptionDataManager(ITableConnection * paintConsumptionConnection);

	void importData(std::map<std::string, AutoValue> const &);
	std::map<std::string, AutoValue> exportData() const;

	void clear();

	void setName(std::string const &);
	std::string getName() const;

	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getMaterialTypes() const;
	double getPaintConsumption(std::string const & paintType, std::string const & materialType) const;

	inline double calculate() const { throw std::runtime_error("PaintConsumptionDispatcher does no calculations"); }
};

#endif
