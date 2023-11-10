#include <cstddef>
#include <stdexcept>

#include <NullValue.hpp>

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

void clearParam(std::map<std::string, AutoValue> & params, std::string const & key) {
	params.at(key) = NullValue();
}

void setParam(std::map<std::string, AutoValue> & params, std::string const & key, AutoValue const & value, std::vector<std::string> const & paramsToClear = { PRESET_NAME }) {
	if (params.at(key) == value)
		return;

	params.at(key) = value;
	for (std::string const & paramName : paramsToClear)
		clearParam(params, paramName);
}

template <typename T>
T getParam(std::map<std::string, AutoValue> const & params, std::string const & key) {
	try {
		AutoValue const & param = params.at(key);
		if (!param.isNull())
			return param;
	} catch (std::out_of_range const &) {}
	throw UndefinedValueException(key);
}

PaintDataContainer::PaintDataContainer(IConnection * conn) : _conn(conn), _params(conn->getPaintPresetTemplate()) {}

std::vector<std::string> PaintDataContainer::getParamNames() const {
	std::vector<std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::map<std::string, std::string> PaintDataContainer::toStringMap() const {
	std::map<std::string, std::string> res;
	for (std::string const & paramName : getParamNames())
		res.at(paramName) = std::string(_params.at(paramName));
	return res;
}

void PaintDataContainer::clear() {
	for (std::string const & paramName : getParamNames())
		clearParam(_params, paramName);
}

std::string PaintDataContainer::getPresetName() const { return getParam<std::string>(_params, PRESET_NAME); }

void PaintDataContainer::setPreset(std::string const & name) {
	_params = _conn->getPaintPreset(name);
	_params.at(PRESET_NAME) = name;
}

std::string PaintDataContainer::getPaintType() const { return getParam<std::string>(_params, PAINT_TYPE); }

void PaintDataContainer::setPaintType(std::string const & type) {
	setParam(_params, PAINT_TYPE, type, { PRESET_NAME, PAINT_CONSUMPTION });
}

std::string PaintDataContainer::getMaterialType() const { return getParam<std::string>(_params, MATERIAL_TYPE); }

void PaintDataContainer::setMaterialType(std::string const & type) {
	setParam(_params, MATERIAL_TYPE, type, { PRESET_NAME, PAINT_CONSUMPTION });
}

double PaintDataContainer::getPaintConsumption() const {
	try {
		return getParam<double>(_params, PAINT_CONSUMPTION);
	} catch (UndefinedValueException const &) {
		AutoValue const & consumption = _conn->getPaintConsumption(getPaintType(), getMaterialType());
		if (consumption.isNull())
			throw UndefinedValueException(PAINT_CONSUMPTION);
		return consumption;
	}
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	setParam(_params, PAINT_CONSUMPTION, value, { PRESET_NAME, PAINT_TYPE, MATERIAL_TYPE });
}


double PaintDataContainer::getDivider() const { return getParam<double>(_params, DIVIDER); }
void PaintDataContainer::setDivider(double value) { setParam(_params, DIVIDER, value); }

double PaintDataContainer::getPercentage() const { return getParam<double>(_params, PERCENTAGE); }
void PaintDataContainer::setPercentage(double value) { setParam(_params, PERCENTAGE, value); }

double PaintDataContainer::getSheetWidth() const { return getParam<double>(_params, SHEET_WIDTH); }
void PaintDataContainer::setSheetWidth(double value) { setParam(_params, SHEET_WIDTH, value); }

double PaintDataContainer::getSheetLength() const { return getParam<double>(_params, SHEET_LENGTH); }
void PaintDataContainer::setSheetLength(double value) { setParam(_params, SHEET_LENGTH, value); }

std::size_t PaintDataContainer::getCirculation() const { return getParam<std::size_t>(_params, CIRCULATION); }
void PaintDataContainer::setCirculation(std::size_t const & value) { setParam(_params, CIRCULATION, value); }

double PaintDataContainer::getPaintReserve() const { return getParam<double>(_params, PAINT_RESERVE); }
void PaintDataContainer::setPaintReserve(double value) { setParam(_params, PAINT_RESERVE, value); }

double PaintDataContainer::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
