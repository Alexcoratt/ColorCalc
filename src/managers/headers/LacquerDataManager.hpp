#ifndef LACQUER_DATA_MANAGER_HPP
#define LACQUER_DATA_MANAGER_HPP

#include "ITableConnection.hpp"
#include "IDataManager.hpp"

#include "UnstableNamedValue.hpp"

class LacquerDataManager : public IDataManager {
private:
	UnstableNamedValue<std::string> _name;

	UnstableNamedValue<double> _percentage;
	UnstableNamedValue<double> _lacquerConsumption;
	UnstableNamedValue<double> _sheetLength;
	UnstableNamedValue<double> _sheetWidth;
	UnstableNamedValue<unsigned long> _circulation;

public:
	LacquerDataManager(ITableConnection *);

	void importData(std::map<std::string, AutoValue> const &);
	std::map<std::string, AutoValue> exportData() const;

	void clear();

	void setName(std::string const &);
	void clearName();
	std::string getName() const;

	double calculate() const;

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
};

#endif
