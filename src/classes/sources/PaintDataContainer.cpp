#include "PaintDataContainer.hpp"
#include "JsonValueIsNullException.hpp"
#include "json_fwd.hpp"

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
	if (isNull(_data[_presetNameColumnName]))
		throw JsonValueIsNullException(_presetNameColumnName);
	return _data[_presetNameColumnName];
}

void PaintDataContainer::setPresetName(std::string const & name) { _data[_presetNameColumnName] = name; }

void PaintDataContainer::clearPresetName() {
	_data[_presetNameColumnName] = nlohmann::json::value_t::null;
}

std::size_t PaintDataContainer::getPaintTypeIndex() const {
	if (isNull(_data[PAINT_TYPE_COLUMN_NAME]))
		throw JsonValueIsNullException(PAINT_TYPE_COLUMN_NAME);
	return _data[PAINT_TYPE_COLUMN_NAME];
}

std::string PaintDataContainer::getPaintTypeName() const { return _conn->getPaintTypeName(getPaintTypeIndex()); }

void PaintDataContainer::setPaintType(std::size_t index) {
	try {
		if (index == getPaintTypeIndex())
			return;
		_data[PAINT_CONSUMPTION_COLUMN_NAME] = _conn->getPaintConsumption(index, getMaterialTypeIndex());
	} catch (JsonValueIsNullException const &) {}

	_data[PAINT_TYPE_COLUMN_NAME] = index;
	clearPresetName();
}

void PaintDataContainer::setPaintType(std::string name) { setPaintType(_conn->getPaintTypeIndex(name)); }

void PaintDataContainer::clearPaintType() { _data[PAINT_TYPE_COLUMN_NAME] = nlohmann::json::value_t::null; }

std::size_t PaintDataContainer::getMaterialTypeIndex() const {
	if (isNull(_data[MATERIAL_TYPE_COLUMN_NAME]))
		throw JsonValueIsNullException(MATERIAL_TYPE_COLUMN_NAME);
	return _data[MATERIAL_TYPE_COLUMN_NAME];
}

std::string PaintDataContainer::getMaterialTypeName() const { return _conn->getMaterialTypeName(getMaterialTypeIndex()); }

void PaintDataContainer::setMaterialType(std::size_t index) {
	try {
		if (index == getMaterialTypeIndex())
			return;
		_data[PAINT_CONSUMPTION_COLUMN_NAME] = _conn->getPaintConsumption(getPaintTypeIndex(), index);
	} catch (JsonValueIsNullException const &) {}

	_data[MATERIAL_TYPE_COLUMN_NAME] = index;
	clearPresetName();
}

void PaintDataContainer::setMaterialType(std::string name) { setMaterialType(_conn->getMaterialTypeIndex(name)); }

void PaintDataContainer::clearMaterialType() { _data[MATERIAL_TYPE_COLUMN_NAME] = nlohmann::json::value_t::null; }

double PaintDataContainer::getPaintConsumption() const {
	if (isNull(_data[PAINT_CONSUMPTION_COLUMN_NAME])) {
		return _conn->getPaintConsumption(getPaintTypeIndex(), getMaterialTypeIndex());
	}
	return _data[PAINT_CONSUMPTION_COLUMN_NAME];
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataContainer::setPaintConsumption(double value) {
	try {
		if (value == getPaintConsumption())
			return;
	} catch (JsonValueIsNullException const &) {}

	_data[PAINT_CONSUMPTION_COLUMN_NAME] = value;
	clearPaintType();
	clearMaterialType();
	clearPresetName();
}

void PaintDataContainer::clearPaintConsumption() {
	_data[PAINT_CONSUMPTION_COLUMN_NAME] = nlohmann::json::value_t::null;
}


double PaintDataContainer::getDivider() const {
	if (isNull(_data[DIVIDER_COLUMN_NAME]))
		throw JsonValueIsNullException(DIVIDER_COLUMN_NAME);
	return _data[DIVIDER_COLUMN_NAME];
}

void PaintDataContainer::setDivider(double value) {

}
