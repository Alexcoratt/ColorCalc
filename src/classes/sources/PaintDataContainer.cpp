#include "PaintDataContainer.hpp"
#include "JsonValueIsNullException.hpp"
#include "json_fwd.hpp"
#include <cstddef>
#include <stdexcept>

#define PAINT_CALCULATION_TABLE_NAME "расчет печатной краски"
#define LACQUER_CALCULATION_TABLE_NAME "расчет лака"

#define PAINT_TYPE_COLUMN_NAME "тип краски"
#define MATERIAL_TYPE_COLUMN_NAME "тип материала"
#define PAINT_CONSUMPTION_COLUMN_NAME "расход краски"
#define DIVIDER_COLUMN_NAME "делитель"
#define PERCENT_COLUMN_NAME "процент запечатки"
#define SHEET_WIDTH_COLUMN_NAME "ширина печатного листа"
#define SHEET_LENGTH_COLUMN_NAME "длина печатного листа"
#define CIRCULATION_COLUMN_NAME "тираж"
#define PAINT_RESERVE_COLUMN_NAME "запас краски"


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
	try {
		if (value == getValue<T>(key))
			return;
	} catch (JsonValueIsNullException const &) {}

	_data[key] = value;
}

PaintDataContainer::PaintDataContainer(IConnection * conn) :
	_conn(conn),
	_data(conn->getPresetTemplate(PAINT_CALCULATION_TABLE_NAME)),
	_presetNameColumnName(conn->getColumnsNames(PAINT_CALCULATION_TABLE_NAME)[conn->getPresetNameColumnIndex(PAINT_CALCULATION_TABLE_NAME)])
{}

IConnection * PaintDataContainer::getConnection() const { return _conn; }

std::string PaintDataContainer::getPresetNameColumnName() const { return _presetNameColumnName; }

std::vector<std::string> PaintDataContainer::getColumnsNames() const { return _conn->getColumnsNames(PAINT_CALCULATION_TABLE_NAME); }

nlohmann::json PaintDataContainer::getData() const { return _data; }

nlohmann::json PaintDataContainer::getData(std::string const & key) const { return _data[key]; }

void PaintDataContainer::setData(std::string const & key, nlohmann::json const & value) { _data[key] = value; }

std::string PaintDataContainer::getPresetName() const {
	return getValue<std::string>(_presetNameColumnName);
}

void PaintDataContainer::setPresetName(std::string const & name) {
	_data[_presetNameColumnName] = name;
}

std::size_t PaintDataContainer::getPaintTypeIndex() const {
	return getValue<std::size_t>(PAINT_TYPE_COLUMN_NAME);
}

std::string PaintDataContainer::getPaintTypeName() const {
	return _conn->getPaintTypeName(getPaintTypeIndex());
}

void PaintDataContainer::setPaintType(std::size_t index) {
	try {
		if (index == getPaintTypeIndex())
			return;
		_data[PAINT_CONSUMPTION_COLUMN_NAME] = _conn->getPaintConsumption(index, getMaterialTypeIndex());
	} catch (JsonValueIsNullException const &) {
	} catch (std::invalid_argument const &) {}

	_data[PAINT_TYPE_COLUMN_NAME] = index;
	clear(_presetNameColumnName);
}

void PaintDataContainer::setPaintType(std::string name) {
	setPaintType(_conn->getPaintTypeIndex(name));
}

std::size_t PaintDataContainer::getMaterialTypeIndex() const {
	return getValue<std::size_t>(MATERIAL_TYPE_COLUMN_NAME);
}

std::string PaintDataContainer::getMaterialTypeName() const {
	return _conn->getMaterialTypeName(getMaterialTypeIndex());
}

void PaintDataContainer::setMaterialType(std::size_t index) {
	try {
		if (index == getMaterialTypeIndex())
			return;
		_data[PAINT_CONSUMPTION_COLUMN_NAME] = _conn->getPaintConsumption(getPaintTypeIndex(), index);
	} catch (JsonValueIsNullException const &) {
	} catch (std::invalid_argument const &) {}

	_data[MATERIAL_TYPE_COLUMN_NAME] = index;
	clear(_presetNameColumnName);
}

void PaintDataContainer::setMaterialType(std::string name) {
	setMaterialType(_conn->getMaterialTypeIndex(name));
}

double PaintDataContainer::getPaintConsumption() const {
	if (isNull(_data[PAINT_CONSUMPTION_COLUMN_NAME])) {
		try {
			return _conn->getPaintConsumption(getPaintTypeIndex(), getMaterialTypeIndex());
		} catch (std::invalid_argument const &) {
			throw JsonValueIsNullException(PAINT_CONSUMPTION_COLUMN_NAME);
		}
	}
	return _data[PAINT_CONSUMPTION_COLUMN_NAME];
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	setValue(PAINT_CONSUMPTION_COLUMN_NAME, value);
	clear(PAINT_TYPE_COLUMN_NAME);
	clear(MATERIAL_TYPE_COLUMN_NAME);
	clear(_presetNameColumnName);
}


double PaintDataContainer::getDivider() const {
	return getValue<double>(DIVIDER_COLUMN_NAME);
}

void PaintDataContainer::setDivider(double value) {
	setValue(DIVIDER_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}


double PaintDataContainer::getPercent() const {
	return getValue<double>(PERCENT_COLUMN_NAME);
}

void PaintDataContainer::setPercent(double value) {
	setValue(PERCENT_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}


double PaintDataContainer::getWidth() const {
	return getValue<double>(SHEET_WIDTH_COLUMN_NAME);
}

void PaintDataContainer::setWidth(double value) {
	setValue(SHEET_WIDTH_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}


double PaintDataContainer::getLength() const {
	return getValue<double>(SHEET_LENGTH_COLUMN_NAME);
}

void PaintDataContainer::setLength(double value) {
	setValue(SHEET_LENGTH_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}


std::size_t PaintDataContainer::getCirculation() const {
	return getValue<std::size_t>(CIRCULATION_COLUMN_NAME);
}

void PaintDataContainer::setCirculation(std::size_t value) {
	setValue(CIRCULATION_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}


double PaintDataContainer::getPaintReserve() const {
	return getValue<double>(PAINT_RESERVE_COLUMN_NAME);
}

void PaintDataContainer::setPaintReserve(double value) {
	setValue(PAINT_RESERVE_COLUMN_NAME, value);
	clear(_presetNameColumnName);
}
