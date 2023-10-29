#include <cstddef>
#include <stdexcept>

#include "PaintDataContainer.hpp"
#include "UndefinedValueException.hpp"
#include "common_methods.hpp"

#define PAINT_TYPE "тип краски"
#define MATERIAL_TYPE "тип материала"
#define PAINT_CONSUMPTION "расход краски"
#define DIVIDER "делитель"
#define PERCENTAGE "процент запечатки"
#define SHEET_WIDTH "ширина печатного листа"
#define SHEET_LENGTH "длина печатного листа"
#define CIRCULATION "тираж"
#define PAINT_RESERVE "запас краски"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

void PaintDataContainer::clear(std::string const & key) {
	_data[key] = nlohmann::json::value_t::null;
}

template <typename T>
T PaintDataContainer::getValue(std::string const & key) const {
	if (common_methods::jsonIsNull(_data[key]))
		throw UndefinedValueException(key);
	return _data[key];
}

template <typename T>
void PaintDataContainer::setValue(std::string const & key, T value) {
	_presetName.clear();
	_data[key] = value;
}

PaintDataContainer::PaintDataContainer(IConnection * conn) : _conn(conn), _data(conn->getPaintPresetTemplate()) {}

IConnection * PaintDataContainer::getConnection() const { return _conn; }

std::vector<std::string> PaintDataContainer::getColumns() const { return _conn->getPaintColumns(); }

void PaintDataContainer::clearData() {
	_presetName.clear();
	_data = _conn->getPaintPresetTemplate();
}

nlohmann::json PaintDataContainer::exportData() const {
	nlohmann::json res = _data;

	try {
		res[PAINT_CONSUMPTION] = getPaintConsumption();
	} catch (UndefinedValueException const &) {
		res[PAINT_CONSUMPTION] = nlohmann::json::value_t::null;
	}

	return res;
}

std::string PaintDataContainer::getPresetName() const {
	if (_presetName.size() > 0)
		return _presetName;
	throw UndefinedValueException("preset name");
}

void PaintDataContainer::setPreset(std::string const & name) {
	_presetName = name;
	_data = _conn->getPaintPreset(name);
}

std::string PaintDataContainer::getPaintType() const { return getValue<std::string>(PAINT_TYPE); }

void PaintDataContainer::setPaintType(std::string type) {
	setValue(PAINT_TYPE, type);
	clear(PAINT_CONSUMPTION);
}

std::string PaintDataContainer::getMaterialType() const { return getValue<std::string>(MATERIAL_TYPE); }

void PaintDataContainer::setMaterialType(std::string type) {
	setValue(MATERIAL_TYPE, type);
	clear(PAINT_CONSUMPTION);
}

double PaintDataContainer::getPaintConsumption() const {
	try {
		return getValue<double>(PAINT_CONSUMPTION);
	} catch (UndefinedValueException const &) {
		return _conn->getPaintConsumption(getPaintType(), getMaterialType());
	}
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	setValue(PAINT_CONSUMPTION, value);
	clear(PAINT_TYPE);
	clear(MATERIAL_TYPE);
}


double PaintDataContainer::getDivider() const { return getValue<double>(DIVIDER); }
void PaintDataContainer::setDivider(double value) { setValue(DIVIDER, value); }

double PaintDataContainer::getPercentage() const { return getValue<double>(PERCENTAGE); }
void PaintDataContainer::setPercentage(double value) { setValue(PERCENTAGE, value); }

double PaintDataContainer::getSheetWidth() const { return getValue<double>(SHEET_WIDTH); }
void PaintDataContainer::setSheetWidth(double value) { setValue(SHEET_WIDTH, value); }

double PaintDataContainer::getSheetLength() const { return getValue<double>(SHEET_LENGTH); }
void PaintDataContainer::setSheetLength(double value) { setValue(SHEET_LENGTH, value); }

std::size_t PaintDataContainer::getCirculation() const { return getValue<std::size_t>(CIRCULATION); }
void PaintDataContainer::setCirculation(std::size_t value) { setValue(CIRCULATION, value); }

double PaintDataContainer::getPaintReserve() const { return getValue<double>(PAINT_RESERVE); }
void PaintDataContainer::setPaintReserve(double value) { setValue(PAINT_RESERVE, value); }

double PaintDataContainer::calculatePaintAmount() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
