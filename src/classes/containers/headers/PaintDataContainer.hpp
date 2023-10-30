#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include "IConnection.hpp"
#include "AbstractDataContainer.hpp"

class PaintDataContainer : public AbstractDataContainer {
public:
	PaintDataContainer(IConnection *);

	std::vector<std::string> getColumns() const;
	nlohmann::json exportData() const;

	void clearData();

	std::vector<std::string> getAvailablePresetsNames() const;

	void setPreset(std::string const &);

	std::string getPaintType() const;
	void setPaintType(std::string);

	std::string getMaterialType() const;
	void setMaterialType(std::string);

	double getPaintConsumption() const;
	void setPaintConsumption(double);

	double getDivider() const;
	void setDivider(double);

	double getPercentage() const;
	void setPercentage(double);

	double getSheetWidth() const;
	void setSheetWidth(double);

	double getSheetLength() const;
	void setSheetLength(double);

	std::size_t getCirculation() const;
	void setCirculation(std::size_t);

	double getPaintReserve() const;
	void setPaintReserve(double);

	double calculate() const;
};

#endif
