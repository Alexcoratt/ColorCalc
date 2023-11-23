#ifndef FOIL_DATA_DISPATCHER_HPP
#define FOIL_DATA_DISPATCHER_HPP

#include "IDataManager.hpp"
#include "ITableConnection.hpp"
#include "UnstableNamedValue.hpp"

#include "FoilRollsDataManager.hpp"

class FoilDataManager : public IDataManager {
private:
	FoilRollsDataManager const * _foilRollsDataManager;

	UnstableNamedValue<std::string> _name;

	UnstableNamedValue<unsigned long> _circulation;
	UnstableNamedValue<double> _length;
	UnstableNamedValue<double> _width;
	UnstableNamedValue<unsigned long> _sheetNumber;
	UnstableNamedValue<double> _lengthReserve;
	UnstableNamedValue<double> _widthReserve;

public:
	FoilDataManager(ITableConnection *, FoilRollsDataManager const *);

	void importData(std::map<std::string, AutoValue> const &);
	std::map<std::string, AutoValue> exportData() const;

	void clear();

	void setName(std::string const &);
	void clearName();
	std::string getName() const;

	double calculate() const;

	std::size_t getCirculation() const;
	void setCirculation(std::size_t const &);

	double getLength() const;
	void setLength(double);

	double getWidth() const;
	void setWidth(double);

	std::size_t getSheetNumber() const;
	void setSheetNumber(std::size_t const &);

	double getLengthReserve() const;
	void setLengthReserve(double);

	double getWidthReserve() const;
	void setWidthReserve(double);

	std::vector<std::string> getSuitableFoilRolls() const;
};

#endif
