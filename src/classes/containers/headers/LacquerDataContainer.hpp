#ifndef LACQUER_DATA_CONTAINER_HPP
#define LACQUER_DATA_CONTAINER_HPP

#include "nlohmann/json.hpp"
#include "IConnection.hpp"
#include "AbstractDataContainer.hpp"

class LacquerDataContainer : public AbstractDataContainer {

public:
	LacquerDataContainer(IConnection *);

	std::vector<std::string> getColumns() const;
	nlohmann::json exportData() const;

	void clearData();

	std::vector<std::string> getAvailablePresetsNames() const;

	void setPreset(std::string const &);

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
