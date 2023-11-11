#include <stdexcept>

#include "LacquerDataContainer.hpp"
#include "UndefinedValueException.hpp"

#define PERCENTAGE "percentage"
#define LACQUER_CONSUMPTION "lacquer_consumption"
#define SHEET_LENGTH "sheet_length"
#define SHEET_WIDTH "sheet_width"
#define CIRCULATION "circulation"

namespace ccm = common_container_methods;

LacquerDataContainer::LacquerDataContainer(IConnection * conn) : _conn(conn), _params(conn->getLacquerPresetTemplate()) {}

IConnection * LacquerDataContainer::getConnection() const { return _conn; }

std::vector<std::string> LacquerDataContainer::getParamNames() const {
	std::vector<std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::map<std::string, std::string> LacquerDataContainer::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res[it->first] = (std::string)it->second;
	return res;
}

std::string LacquerDataContainer::getPresetName() const {
	if (_presetName.isNull())
		throw UndefinedValueException("preset name");
	return _presetName;
}

void LacquerDataContainer::setPreset(std::string const & name) {
	if ((std::string)_presetName == name)
		return;

	auto params = _conn->getLacquerPreset(name);
	std::vector<std::string> doubleValuedColumns = {
		PERCENTAGE,
		LACQUER_CONSUMPTION,
		SHEET_WIDTH,
		SHEET_LENGTH,
	};

	for (std::string column : doubleValuedColumns) {
		AutoValue & value = params.at(column);
		if (!value.isNull())
			value = std::stod(value);
	}

	if (!params[CIRCULATION].isNull())
		params[CIRCULATION] = std::stoul(params[CIRCULATION]);

	_presetName = name;
	_params = params;
}

void LacquerDataContainer::clear() { _params = _conn->getLacquerPresetTemplate(); }

double LacquerDataContainer::getPercentage() const { return ccm::getParam(_params, PERCENTAGE); }
void LacquerDataContainer::setPercentage(double value) {
	if ((double)_params.at(PERCENTAGE) == value)
		return;

	_params.at(PERCENTAGE) = value;
	_presetName.clear();
}

double LacquerDataContainer::getLacquerConsumption() const { return ccm::getParam(_params, LACQUER_CONSUMPTION); }
void LacquerDataContainer::setLacquerConsumption(double value) {
	if ((double)_params.at(LACQUER_CONSUMPTION) == value)
		return;

	_params.at(LACQUER_CONSUMPTION) = value;
	_presetName.clear();
}

double LacquerDataContainer::getSheetLength() const { return ccm::getParam(_params, SHEET_LENGTH); }
void LacquerDataContainer::setSheetLength(double value) {
	if ((double)_params.at(SHEET_LENGTH) == value)
		return;

	_params.at(SHEET_LENGTH) = value;
	_presetName.clear();
}

double LacquerDataContainer::getSheetWidth() const { return ccm::getParam(_params, SHEET_WIDTH); }
void LacquerDataContainer::setSheetWidth(double value) {
	if ((double)_params.at(SHEET_WIDTH) == value)
		return;

	_params.at(SHEET_WIDTH) = value;
	_presetName.clear();
}

std::size_t LacquerDataContainer::getCirculation() const { return ccm::getParam(_params, CIRCULATION); }
void LacquerDataContainer::setCirculation(std::size_t value) {
	if ((std::size_t)_params.at(CIRCULATION) == value)
		return;

	_params.at(CIRCULATION) = value;
	_presetName.clear();
}

double LacquerDataContainer::calculate() const {
	return getSheetLength() * getSheetWidth() / 1000000 * getLacquerConsumption() / 1000 * getCirculation() * getPercentage() / 100;
}
