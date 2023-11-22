#include <array>
#include <iostream>

#include "FoilDataManager.hpp"
#include "auxillary_methods.hpp"

#define CIRCULATION "circulation"
#define LENGTH "length"
#define WIDTH "width"
#define SHEET_NUMBER "sheet_number"
#define LENGTH_RESERVE "length_reserve"
#define WIDTH_RESERVE "width_reserve"

FoilDataManager::FoilDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

void FoilDataManager::importData(std::map<std::string, AutoValue> const & params) {
	auxillary_methods::setParam(_circulation, CIRCULATION, params);
	auxillary_methods::setParam(_length, LENGTH, params);
	auxillary_methods::setParam(_width, WIDTH, params);
	auxillary_methods::setParam(_sheetNumber, SHEET_NUMBER, params);
	auxillary_methods::setParam(_lengthReserve, LENGTH_RESERVE, params);
	auxillary_methods::setParam(_widthReserve, WIDTH_RESERVE, params);
}

template <typename T>
void setValue(UnstableNamedValue<T> const & param, std::map<std::string, AutoValue> & map) { map[param.getName()] = param.getValue(); }

std::map<std::string, AutoValue> FoilDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	setValue(_circulation, res);
	setValue(_length, res);
	setValue(_width, res);
	setValue(_sheetNumber, res);
	setValue(_lengthReserve, res);
	setValue(_widthReserve, res);
	return res;
}

void FoilDataManager::clear() {
	clearName();
	_circulation.clear();
	_length.clear();
	_width.clear();
	_sheetNumber.clear();
	_lengthReserve.clear();
	_widthReserve.clear();
}

void FoilDataManager::setName(std::string const & name) { _name = name; }
void FoilDataManager::clearName() { _name.clear(); }
std::string FoilDataManager::getName() const { return _name; }

std::size_t FoilDataManager::getCirculation() const { return _circulation; }
void FoilDataManager::setCirculation(std::size_t const & value) {
	if (_circulation == value)
		return;

	_circulation = value;
	clearName();
}

double FoilDataManager::getLength() const { return _length; }
void FoilDataManager::setLength(double value) {
	if (_length == value)
		return;

	_length = value;
	clearName();
}

double FoilDataManager::getWidth() const { return _width; }
void FoilDataManager::setWidth(double value) {
	if (_width == value)
		return;

	_width = value;
	clearName();
}

std::size_t FoilDataManager::getSheetNumber() const { return _sheetNumber; }
void FoilDataManager::setSheetNumber(std::size_t const & value) {
	if (_sheetNumber == value)
		return;

	_sheetNumber = value;
	clearName();
}

double FoilDataManager::getLengthReserve() const { return _lengthReserve; }
void FoilDataManager::setLengthReserve(double value) {
	if (_lengthReserve == value)
		return;

	_lengthReserve = value;
	clearName();
}

double FoilDataManager::getWidthReserve() const { return _widthReserve; }
void FoilDataManager::setWidthReserve(double value) {
	if (_widthReserve == value)
		return;

	_widthReserve = value;
	clearName();
}

std::vector<std::string> FoilDataManager::getSuitableFoilRolls() const {
	// FIXME
	std::cerr << "coming soon\n";
	return {};
}

double FoilDataManager::calculate() const { return (getLength() + getLengthReserve()) * getCirculation() / getSheetNumber() / 1000; }
