#ifndef PAINT_DATA_CONTAINER_HPP
#define PAINT_DATA_CONTAINER_HPP

#include <string>
#include "AbstractDataContainer.hpp"
#include "UnstableNamedValue.hpp"

class PaintDataContainer : public AbstractDataContainer {
private:
	UnstableNamedValue<std::string> _presetName;
	UnstableNamedValue<std::string> _paintType;
	UnstableNamedValue<std::string> _materialType;
	UnstableNamedValue<double> _paintConsumption;
	UnstableNamedValue<double> _divider;
	UnstableNamedValue<double> _percentage;
	UnstableNamedValue<double> _sheetWidth;
	UnstableNamedValue<double> _sheetLength;
	UnstableNamedValue<std::size_t> _circulation;
	UnstableNamedValue<double> _paintReserve;

public:
	PaintDataContainer(
		UnstableNamedValue<std::string> const &,
		UnstableNamedValue<std::string> const &,
		UnstableNamedValue<std::string> const &,
		UnstableNamedValue<double> const &,
		UnstableNamedValue<double> const &,
		UnstableNamedValue<double> const &,
		UnstableNamedValue<double> const &,
		UnstableNamedValue<double> const &,
		UnstableNamedValue<std::size_t> const &,
		UnstableNamedValue<double> const &
	);

	std::vector<std::string> getParamNames() const;
	std::map<std::string, std::string> toStringMap() const;

	void clear();

	std::string getPresetName() const;
	void setPresetName(std::string const &);

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
