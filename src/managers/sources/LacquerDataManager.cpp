#include <stdexcept>

#include "LacquerDataManager.hpp"

#define PERCENTAGE "percentage"
#define LACQUER_CONSUMPTION "lacquer_consumption"
#define SHEET_LENGTH "sheet_length"
#define SHEET_WIDTH "sheet_width"
#define CIRCULATION "circulation"

LacquerDataManager::LacquerDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

template <typename T>
void setParam(UnstableNamedValue<T> & param, std::string const & key, std::map<std::string, AutoValue> const & params) {
	param.setName(key);
	auto value = params.at(key);
	if (!value.isNull())
		param.setValue((T)value);
}

void LacquerDataManager::importData(std::map<std::string, AutoValue> const & params) {
	setParam(_percentage, PERCENTAGE, params);
	setParam(_lacquerConsumption, LACQUER_CONSUMPTION, params);
	setParam(_sheetLength, SHEET_LENGTH, params);
	setParam(_sheetWidth, SHEET_WIDTH, params);
	setParam(_circulation, CIRCULATION, params);
}

template <typename T>
void setValue(UnstableNamedValue<T> const & param, std::map<std::string, AutoValue> & map) { map[param.getName()] = param.getValue(); }

std::map<std::string, AutoValue> LacquerDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	setValue(_percentage, res);
	setValue(_lacquerConsumption, res);
	setValue(_sheetLength, res);
	setValue(_sheetWidth, res);
	setValue(_circulation, res);
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

double LacquerDataManager::getPercentage() const { return _percentage; }
void LacquerDataManager::setPercentage(double value) {
	if (_percentage == value)
		return;

	_percentage = value;
	_name.clear();
}

double LacquerDataManager::getLacquerConsumption() const { return _lacquerConsumption; }
void LacquerDataManager::setLacquerConsumption(double value) {
	if (_lacquerConsumption == value)
		return;

	_lacquerConsumption = value;
	_name.clear();
}

double LacquerDataManager::getSheetLength() const { return _sheetLength; }
void LacquerDataManager::setSheetLength(double value) {
	if (_sheetLength == value)
		return;

	_sheetLength = value;
	_name.clear();
}

double LacquerDataManager::getSheetWidth() const { return _sheetWidth; }
void LacquerDataManager::setSheetWidth(double value) {
	if (_sheetWidth == value)
		return;

	_sheetWidth = value;
	_name.clear();
}

std::size_t LacquerDataManager::getCirculation() const { return _circulation; }
void LacquerDataManager::setCirculation(std::size_t value) {
	if (_circulation == value)
		return;

	_circulation = value;
	_name.clear();
}

double LacquerDataManager::calculate() const {
	return getSheetLength() * getSheetWidth() / 1000000 * getLacquerConsumption() / 1000 * getCirculation() * getPercentage() / 100;
}
