#include <cstddef>
#include "PaintDataContainer.hpp"
#include "UndefinedValueException.hpp"

#define PRESET_NAME "preset_name"
#define PAINT_TYPE "paint_type"
#define MATERIAL_TYPE "material_type"
#define PAINT_CONSUMPTION "paint_consumption"
#define DIVIDER "divider"
#define PERCENTAGE "percentage"
#define SHEET_WIDTH "sheet_width"
#define SHEET_LENGTH "sheet_length"
#define CIRCULATION "circulation"
#define PAINT_RESERVE "paint_reserve"

PaintDataContainer::PaintDataContainer(IConnection * conn) : _conn(conn), _params(conn->getPaintPresetTemplate()) {}

IConnection * PaintDataContainer::getConnection() const { return _conn; }

std::vector<std::string> PaintDataContainer::getParamNames() const {
	std::vector<std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::map<std::string, std::string> PaintDataContainer::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto iter = _params.begin(); iter != _params.end(); ++iter)
		res[iter->first] = (std::string)iter->second;

	try {
		res[PAINT_CONSUMPTION] = getPaintConsumption();
	} catch (UndefinedValueException const &) {}

	return res;
}

void PaintDataContainer::clear() { _params = _conn->getPaintPresetTemplate(); }

std::string PaintDataContainer::getPresetName() const { return _presetName; }

void PaintDataContainer::setPreset(std::string const & name) {
	if ((std::string)_presetName == name)
		return;

	auto params = _conn->getPaintPreset(name);
	std::vector<std::string> doubleValuedColumns = {
		PAINT_CONSUMPTION,
		DIVIDER,
		PERCENTAGE,
		SHEET_WIDTH,
		SHEET_LENGTH,
		PAINT_RESERVE
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

std::string PaintDataContainer::getPaintType() const { return _params.at(PAINT_TYPE); }
void PaintDataContainer::setPaintType(std::string const & type) {
	if ((std::string)_params.at(PAINT_TYPE) == type)
		return;

	_params.at(PAINT_TYPE) = type;
	_params.at(PAINT_CONSUMPTION).clear();
	_presetName.clear();
}

std::string PaintDataContainer::getMaterialType() const { return _params.at(MATERIAL_TYPE); }
void PaintDataContainer::setMaterialType(std::string const & type) {
	if ((std::string)_params.at(MATERIAL_TYPE) == type)
		return;

	_params.at(MATERIAL_TYPE) = type;
	_params.at(PAINT_CONSUMPTION).clear();
	_presetName.clear();
}

double PaintDataContainer::getPaintConsumption() const {
	AutoValue value = _params.at(PAINT_CONSUMPTION);
	if (value.isNull())
		return _conn->getPaintConsumption(getPaintType(), getMaterialType());
	return value;
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	if ((double)_params.at(PAINT_CONSUMPTION) == value)
		return;

	_params.at(PAINT_CONSUMPTION) = value;
	_params.at(PAINT_TYPE).clear();
	_params.at(MATERIAL_TYPE).clear();
	_presetName.clear();
}


double PaintDataContainer::getDivider() const { return _params.at(DIVIDER); }
void PaintDataContainer::setDivider(double value) {
	if ((double)_params.at(DIVIDER) == value)
		return;

	_params.at(DIVIDER) = value;
	_presetName.clear();
}

double PaintDataContainer::getPercentage() const { return _params.at(PERCENTAGE); }
void PaintDataContainer::setPercentage(double value) {
	if ((double)_params.at(PERCENTAGE) == value)
		return;

	_params.at(PERCENTAGE) = value;
	_presetName.clear();
}

double PaintDataContainer::getSheetWidth() const { return _params.at(SHEET_WIDTH); }
void PaintDataContainer::setSheetWidth(double value) {
	if ((double)_params.at(SHEET_WIDTH) == value)
		return;

	_params.at(SHEET_WIDTH) = value;
	_presetName.clear();
}

double PaintDataContainer::getSheetLength() const { return _params.at(SHEET_LENGTH); }
void PaintDataContainer::setSheetLength(double value) {
	if ((double)_params.at(SHEET_LENGTH) == value)
		return;

	_params.at(SHEET_LENGTH) = value;
	_presetName.clear();
}

std::size_t PaintDataContainer::getCirculation() const { return _params.at(CIRCULATION); }
void PaintDataContainer::setCirculation(std::size_t const & value) {
	if ((std::size_t)_params.at(CIRCULATION) == value)
		return;

	_params.at(CIRCULATION) = value;
	_presetName.clear();
}

double PaintDataContainer::getPaintReserve() const { return _params.at(PAINT_RESERVE); }
void PaintDataContainer::setPaintReserve(double value) {
	if ((double)_params.at(PAINT_RESERVE) == value)
		return;

	_params.at(PAINT_RESERVE) = value;
	_presetName.clear();
}

double PaintDataContainer::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
