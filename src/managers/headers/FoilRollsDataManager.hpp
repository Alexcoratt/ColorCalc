#ifndef FOIL_ROLLS_DATA_MANAGER_HPP
#define FOIL_ROLLS_DATA_MANAGER_HPP

#include "IDataManager.hpp"
#include "UnstableNamedValue.hpp"

class FoilRollsDataManager : public IDataManager {
private:
	UnstableNamedValue<std::string> _name;

	UnstableNamedValue<double> _length;
	UnstableNamedValue<double> _width;

public:
	FoilRollsDataManager(ITableConnection *);

	void importData(std::map<std::string, AutoValue> const &);
	std::map<std::string, AutoValue> exportData() const;

	void clear();

	void setName(std::string const &);
	void clearName();
	std::string getName() const;

	double calculate() const;

	double getLength() const;
	void setLength(double);

	double getWidth() const;
	void setWidth(double);
};

#endif
