#include <stdexcept>

#include "LacquerDataManager.hpp"
#include "auxillary_methods.hpp"

#define PERCENTAGE "percentage"
#define LACQUER_CONSUMPTION "lacquer_consumption"
#define SHEET_LENGTH "sheet_length"
#define SHEET_WIDTH "sheet_width"
#define CIRCULATION "circulation"

LacquerDataManager::LacquerDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

void LacquerDataManager::importData(std::map<std::string, AutoValue> const & params) {
	auxillary_methods::setParam(_percentage, params, PERCENTAGE);
	auxillary_methods::setParam(_lacquerConsumption, params, LACQUER_CONSUMPTION);
	auxillary_methods::setParam(_sheetLength, params, SHEET_LENGTH);
	auxillary_methods::setParam(_sheetWidth, params, SHEET_WIDTH);
	auxillary_methods::setParam(_circulation, params, CIRCULATION);
}

std::map<std::string, AutoValue> LacquerDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	auxillary_methods::setMapValue(res, _percentage);
	auxillary_methods::setMapValue(res, _lacquerConsumption);
	auxillary_methods::setMapValue(res, _sheetLength);
	auxillary_methods::setMapValue(res, _sheetWidth);
	auxillary_methods::setMapValue(res, _circulation);
	return res;
}

void LacquerDataManager::clear() {
	_name.clear();
	_percentage.clear();
	_lacquerConsumption.clear();
	_sheetLength.clear();
	_sheetWidth.clear();
	_circulation.clear();
}

void LacquerDataManager::setName(std::string const & name) { _name = name; }
void LacquerDataManager::clearName() { _name.clear(); }
std::string LacquerDataManager::getName() const { return _name; }

double LacquerDataManager::getPercentage() const { return _percentage; }
void LacquerDataManager::setPercentage(double value) {
	if (_percentage == value)
		return;

	_percentage = value;
	_name.clear();
}

void LacquerDataManager::clearPercentage() {
	if (!_percentage.isDefined())
		return;

	_percentage.clear();
	_name.clear();
}

double LacquerDataManager::getLacquerConsumption() const { return _lacquerConsumption; }
void LacquerDataManager::setLacquerConsumption(double value) {
	if (_lacquerConsumption == value)
		return;

	_lacquerConsumption = value;
	_name.clear();
}

void LacquerDataManager::clearLacquerConsumption() {
	if (!_lacquerConsumption.isDefined())
		return;

	_lacquerConsumption.clear();
	_name.clear();
}

double LacquerDataManager::getSheetLength() const { return _sheetLength; }
void LacquerDataManager::setSheetLength(double value) {
	if (_sheetLength == value)
		return;

	_sheetLength = value;
	_name.clear();
}

void LacquerDataManager::clearSheetLength() {
	if (!_sheetLength.isDefined())
		return;

	_sheetLength.clear();
	_name.clear();
}

double LacquerDataManager::getSheetWidth() const { return _sheetWidth; }
void LacquerDataManager::setSheetWidth(double value) {
	if (_sheetWidth == value)
		return;

	_sheetWidth = value;
	_name.clear();
}

void LacquerDataManager::clearSheetWidth() {
	if (!_sheetWidth.isDefined())
		return;

	_sheetWidth.clear();
	_name.clear();
}

unsigned long LacquerDataManager::getCirculation() const { return _circulation; }
void LacquerDataManager::setCirculation(unsigned long value) {
	if (_circulation == value)
		return;

	_circulation = value;
	_name.clear();
}

void LacquerDataManager::clearCirculation() {
	if (!_circulation.isDefined())
		return;

	_circulation.clear();
	_name.clear();
}

double LacquerDataManager::calculate() const {
	return getSheetLength() * getSheetWidth() / 1000000 * getLacquerConsumption() / 1000 * getCirculation() * getPercentage() / 100;
}
