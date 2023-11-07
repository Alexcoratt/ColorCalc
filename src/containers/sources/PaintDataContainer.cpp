#include <cstddef>
#include <stdexcept>

#include "PaintDataContainer.hpp"
#include "UndefinedValueException.hpp"

#define PAINT_TYPE "тип краски"
#define MATERIAL_TYPE "тип материала"
#define PAINT_CONSUMPTION "расход краски"
#define DIVIDER "делитель"
#define PERCENTAGE "процент запечатки"
#define SHEET_WIDTH "ширина печатного листа"
#define SHEET_LENGTH "длина печатного листа"
#define CIRCULATION "тираж"
#define PAINT_RESERVE "запас краски"

PaintDataContainer::PaintDataContainer(IConnection * conn) {
	_conn = conn;
	_data = conn->getPaintPresetTemplate();
}

std::vector<std::string> PaintDataContainer::getColumns() const { return _conn->getPaintColumns(); }

nlohmann::json PaintDataContainer::exportData() const {
	nlohmann::json res = _data;

	try {
		res[PAINT_CONSUMPTION] = getPaintConsumption();
	} catch (UndefinedValueException const &) {
		res[PAINT_CONSUMPTION] = nlohmann::json::value_t::null;
	}

	return res;
}

void PaintDataContainer::clearData() {
	_presetName.clear();
	_data = _conn->getPaintPresetTemplate();
}

std::vector<std::string> PaintDataContainer::getAvailablePresetsNames() const { return _conn->getPaintPresetsNames(); }

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

double PaintDataContainer::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
