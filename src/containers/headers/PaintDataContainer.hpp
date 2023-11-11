#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include <AutoValue.hpp>

#include "AbstractDataContainer.hpp"
#include "IConnection.hpp"

class PaintDataContainer : public AbstractDataContainer {
private:
	IConnection * _conn;
	std::map<std::string, AutoValue> _params;
	AutoValue _presetName;

public:
	PaintDataContainer(IConnection *);

	IConnection * getConnection() const;

	std::vector<std::string> getParamNames() const;
	std::map<std::string, std::string> toStringMap() const;

	void clear();

	std::string getPresetName() const;
	void setPreset(std::string const &);

	std::string getPaintType() const;
	void setPaintType(std::string const &);

	std::string getMaterialType() const;
	void setMaterialType(std::string const &);

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
	void setCirculation(std::size_t const &);

	double getPaintReserve() const;
	void setPaintReserve(double);

	double calculate() const;
};

#endif
