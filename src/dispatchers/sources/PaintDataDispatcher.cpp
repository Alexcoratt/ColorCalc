#include <cstddef>
#include <iostream>

#include "PaintDataDispatcher.hpp"

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

namespace ccm = common_container_methods;

PaintDataDispatcher::PaintDataDispatcher(IConnection * conn) : _conn(conn), _params(conn->getPaintPresetTemplate()) {}

IConnection * PaintDataDispatcher::getConnection() const { return _conn; }

std::vector<std::string> PaintDataDispatcher::getAvailablePresetNames() const { return _conn->getPaintPresetNames(); }

std::vector<std::string> PaintDataDispatcher::getParamNames() const {
	std::vector<std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::map<std::string, std::string> PaintDataDispatcher::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto iter = _params.begin(); iter != _params.end(); ++iter)
		res[iter->first] = (std::string)iter->second;

	try {
		res[PAINT_CONSUMPTION] = std::to_string(getPaintConsumption());
	} catch (UndefinedValueException const &) {}

	return res;
}

void PaintDataDispatcher::clear() {
	_presetName.clear();
	_params = _conn->getPaintPresetTemplate();
}

std::string PaintDataDispatcher::getPresetName() const {
	if (_presetName.empty())
		throw UndefinedValueException("preset name");
	return _presetName;
}

void PaintDataDispatcher::setPreset(std::string const & name) {
	if (_presetName == name)
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

void PaintDataDispatcher::createPreset(std::string const & name) {
	_conn->createPaintPreset(name, _params);
	_presetName = name;
}

void PaintDataDispatcher::updatePreset(std::string const & name) {
	_conn->updatePaintPreset(name, _params);
}

void PaintDataDispatcher::removePreset(std::string const & name) {
	_conn->removePaintPreset(name);
}

std::string PaintDataDispatcher::getPaintType() const { return ccm::getParam(_params, PAINT_TYPE); }
void PaintDataDispatcher::setPaintType(std::string const & type) {
	if ((std::string)_params.at(PAINT_TYPE) == type)
		return;

	_params.at(PAINT_TYPE) = type;
	_params.at(PAINT_CONSUMPTION).clear();
	_presetName.clear();
}

std::string PaintDataDispatcher::getMaterialType() const { return ccm::getParam(_params, MATERIAL_TYPE); }
void PaintDataDispatcher::setMaterialType(std::string const & type) {
	if ((std::string)_params.at(MATERIAL_TYPE) == type)
		return;

	_params.at(MATERIAL_TYPE) = type;
	_params.at(PAINT_CONSUMPTION).clear();
	_presetName.clear();
}

double PaintDataDispatcher::getPaintConsumption() const {
	AutoValue value = _params.at(PAINT_CONSUMPTION);
	if (value.isNull())
		return _conn->getPaintConsumption(getPaintType(), getMaterialType());
	return value;
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataDispatcher::setPaintConsumption(double value) {
	if ((double)_params.at(PAINT_CONSUMPTION) == value)
		return;

	_params.at(PAINT_CONSUMPTION) = value;
	_params.at(PAINT_TYPE).clear();
	_params.at(MATERIAL_TYPE).clear();
	_presetName.clear();
}


double PaintDataDispatcher::getDivider() const { return ccm::getParam(_params, DIVIDER); }
void PaintDataDispatcher::setDivider(double value) {
	if ((double)_params.at(DIVIDER) == value)
		return;

	_params.at(DIVIDER) = value;
	_presetName.clear();
}

double PaintDataDispatcher::getPercentage() const { return ccm::getParam(_params, PERCENTAGE); }
void PaintDataDispatcher::setPercentage(double value) {
	if ((double)_params.at(PERCENTAGE) == value)
		return;

	_params.at(PERCENTAGE) = value;
	_presetName.clear();
}

double PaintDataDispatcher::getSheetWidth() const { return ccm::getParam(_params, SHEET_WIDTH); }
void PaintDataDispatcher::setSheetWidth(double value) {
	if ((double)_params.at(SHEET_WIDTH) == value)
		return;

	_params.at(SHEET_WIDTH) = value;
	_presetName.clear();
}

double PaintDataDispatcher::getSheetLength() const { return ccm::getParam(_params, SHEET_LENGTH); }
void PaintDataDispatcher::setSheetLength(double value) {
	if ((double)_params.at(SHEET_LENGTH) == value)
		return;

	_params.at(SHEET_LENGTH) = value;
	_presetName.clear();
}

std::size_t PaintDataDispatcher::getCirculation() const { return ccm::getParam(_params, CIRCULATION); }
void PaintDataDispatcher::setCirculation(std::size_t const & value) {
	if ((std::size_t)_params.at(CIRCULATION) == value)
		return;

	_params.at(CIRCULATION) = value;
	_presetName.clear();
}

double PaintDataDispatcher::getPaintReserve() const { return ccm::getParam(_params, PAINT_RESERVE); }
void PaintDataDispatcher::setPaintReserve(double value) {
	if ((double)_params.at(PAINT_RESERVE) == value)
		return;

	_params.at(PAINT_RESERVE) = value;
	_presetName.clear();
}

double PaintDataDispatcher::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
