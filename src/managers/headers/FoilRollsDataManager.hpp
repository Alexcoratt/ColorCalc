#ifndef FOIL_ROLLS_DATA_MANAGER_HPP
#define FOIL_ROLLS_DATA_MANAGER_HPP

#include "IDataManager.hpp"
#include "UnstableNamedValue.hpp"

class FoilRollsDataDispatcher : public IDataManager {
private:
	std::string _name;
	UnstableNamedValue<double> _length;
	UnstableNamedValue<double> _width;

public:
	FoilRollsDataDispatcher(ITableConnection *);

	void importData(const std::map<std::string, AutoValue> &);
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
