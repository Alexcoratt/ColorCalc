#ifndef PAINT_DATA_MANAGER_HPP
#define PAINT_DATA_MANAGER_HPP

#include <AutoValue.hpp>

#include "IDataManager.hpp"
#include "ITableConnection.hpp"

#include "PaintConsumptionDataManager.hpp"
#include "UnstableNamedValue.hpp"

class PaintDataManager : public IDataManager {
private:
	PaintConsumptionDataManager const * _paintConsumptionManager;
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
	PaintDataManager(ITableConnection * paintTableConnection, PaintConsumptionDataManager const *);

	void importData(std::map<std::string, AutoValue> const &);
	std::map<std::string, AutoValue> exportData() const;

	void clear();

	void setName(std::string const &);
	void clearName();
	std::string getName() const;

	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getMaterialTypes() const;

	std::string getPaintType() const;
	void setPaintType(std::string const &);
	void clearPaintType();

	std::string getMaterialType() const;
	void setMaterialType(std::string const &);
	void clearMaterialType();

	double getPaintConsumption() const;
	void setPaintConsumption(double);
	void clearPaintConsumption();

	double getDivider() const;
	void setDivider(double);
	void clearDivider();

	double getPercentage() const;
	void setPercentage(double);
	void clearPercentage();

	double getSheetWidth() const;
	void setSheetWidth(double);
	void clearSheetWidth();

	double getSheetLength() const;
	void setSheetLength(double);
	void clearSheetLength();

	unsigned long getCirculation() const;
	void setCirculation(unsigned long const &);
	void clearCirculation();

	double getPaintReserve() const;
	void setPaintReserve(double);
	void clearPaintReserve();

	double calculate() const;
};

#endif
