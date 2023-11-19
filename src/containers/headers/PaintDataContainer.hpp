#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include "IDataContainer.hpp"
#include "UnstableNamedValue.hpp"

class PaintDataContainer : public IDataContainer {
private:
	UnstableNamedValue<std::string> _name;
	UnstableNamedValue<std::string> _paintType;
	UnstableNamedValue<std::string> _materialType;
	UnstableNamedValue<double> _paintConsumption;
	UnstableNamedValue<double> _divider;
	UnstableNamedValue<double> _percentage;
	UnstableNamedValue<double> _sheetWidth;
	UnstableNamedValue<double> _sheetLength;
	UnstableNamedValue<unsigned long> _circulation;
	UnstableNamedValue<double> _paintReserve;

public:
	PaintDataContainer(std::map<std::string, AutoValue> const & = {});

	std::map<std::string, AutoValue> exportData() const;
	void importData(std::map<std::string, AutoValue> const &);

	void clear();

	std::string getName() const;
	void setName(std::string const &);

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

	unsigned long getCirculation() const;
	void setCirculation(unsigned long);

	double getPaintReserve() const;
	void setPaintReserve(double);
};

#endif
