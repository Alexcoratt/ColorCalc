#include "LacquerDataContainer.hpp"

#define PERCENTAGE "percentage"
#define LACQUER_CONSUMPTION "lacquer_consumption"
#define SHEET_LENGTH "sheet_length"
#define SHEET_WIDTH "sheet_width"
#define CIRCULATION "circulation"

LacquerDataContainer::LacquerDataContainer(IConnection * conn) {
	_conn = conn;
	_data = conn->getLacquerPresetTemplate();
}

std::vector<std::string> LacquerDataContainer::getColumns() const { return _conn->getLacquerColumns(); }

nlohmann::json LacquerDataContainer::exportData() const { return _data; }

std::vector<std::string> LacquerDataContainer::getAvailablePresetsNames() const { return _conn->getLacquerPresetsNames(); }

void LacquerDataContainer::setPreset(std::string const & name) {
	_presetName = name;
	_data = _conn->getLacquerPreset(name);
}

void LacquerDataContainer::clearData() {
	_presetName.clear();
	_data = _conn->getLacquerPresetTemplate();
}

double LacquerDataContainer::getPercentage() const { return getValue<double>(PERCENTAGE); }
void LacquerDataContainer::setPercentage(double value) { setValue(PERCENTAGE, value); }

double LacquerDataContainer::getLacquerConsumption() const { return getValue<double>(LACQUER_CONSUMPTION); }
void LacquerDataContainer::setLacquerConsumption(double value) { setValue(LACQUER_CONSUMPTION, value); }

double LacquerDataContainer::getSheetLength() const { return getValue<double>(SHEET_LENGTH); }
void LacquerDataContainer::setSheetLength(double value) { setValue(SHEET_LENGTH, value); }

double LacquerDataContainer::getSheetWidth() const { return getValue<double>(SHEET_WIDTH); }
void LacquerDataContainer::setSheetWidth(double value) { setValue(SHEET_WIDTH, value); }

std::size_t LacquerDataContainer::getCirculation() const { return getValue<std::size_t>(CIRCULATION); }
void LacquerDataContainer::setCirculation(std::size_t value) { setValue(CIRCULATION, value); }

double LacquerDataContainer::calculate() const {
	return getSheetLength() * getSheetWidth() / 1000000 * getLacquerConsumption() / 1000 * getCirculation() * getPercentage() / 100;
}
