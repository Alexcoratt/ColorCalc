#include "PaintDataContainer.hpp"
#include "JsonValueIsNullException.hpp"
#include "json_fwd.hpp"
#include <cstddef>
#include <stdexcept>

#define PAINT_TYPE "тип краски"
#define MATERIAL_TYPE "тип материала"
#define PAINT_CONSUMPTION "расход краски"
#define DIVIDER "делитель"
#define PERCENT "процент запечатки"
#define SHEET_WIDTH "ширина печатного листа"
#define SHEET_LENGTH "длина печатного листа"
#define CIRCULATION "тираж"
#define PAINT_RESERVE "запас краски"


bool isNull(nlohmann::json const & value) { return value == nlohmann::json::value_t::null; }

void PaintDataContainer::clear(std::string const & key) {
	_data[key] = nlohmann::json::value_t::null;
}

template <typename T>
T PaintDataContainer::getValue(std::string const & key) const {
	if (isNull(_data[key]))
		throw JsonValueIsNullException(key);
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

std::string PaintDataContainer::getPresetName() const { return _presetName; }

void PaintDataContainer::setPreset(std::string const & name) {
	_presetName = name;
	_data = _conn->getPaintPreset(name);
}

std::string PaintDataContainer::getPaintType() const { return _data[PAINT_TYPE]; }

void PaintDataContainer::setPaintType(std::string type) {
	setValue(PAINT_TYPE, type);
	clear(PAINT_CONSUMPTION);
}

std::string PaintDataContainer::getMaterialType() const { return _data[MATERIAL_TYPE]; }

void PaintDataContainer::setMaterialType(std::string type) {
	setValue(MATERIAL_TYPE, type);
	clear(PAINT_CONSUMPTION);
}

double PaintDataContainer::getPaintConsumption() const {
	if (isNull(_data[PAINT_CONSUMPTION]))
		return _conn->getPaintConsumption(getPaintType(), getMaterialType());
	return _data[PAINT_CONSUMPTION];
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	setValue(PAINT_CONSUMPTION, value);
	clear(PAINT_TYPE);
	clear(MATERIAL_TYPE);
}


double PaintDataContainer::getDivider() const { return getValue<double>(DIVIDER); }
void PaintDataContainer::setDivider(double value) { setValue(DIVIDER, value); }

double PaintDataContainer::getPercent() const { return getValue<double>(PERCENT); }
void PaintDataContainer::setPercent(double value) { setValue(PERCENT, value); }

double PaintDataContainer::getWidth() const { return getValue<double>(SHEET_WIDTH); }
void PaintDataContainer::setWidth(double value) { setValue(SHEET_WIDTH, value); }

double PaintDataContainer::getLength() const { return getValue<double>(SHEET_LENGTH); }
void PaintDataContainer::setLength(double value) { setValue(SHEET_LENGTH, value); }

std::size_t PaintDataContainer::getCirculation() const { return getValue<std::size_t>(CIRCULATION); }
void PaintDataContainer::setCirculation(std::size_t value) { setValue(CIRCULATION, value); }

double PaintDataContainer::getPaintReserve() const { return getValue<double>(PAINT_RESERVE); }
void PaintDataContainer::setPaintReserve(double value) { setValue(PAINT_RESERVE, value); }
