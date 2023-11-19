#include <cstddef>
#include <iostream>

#include "PaintDataDispatcher.hpp"

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

namespace cdm = common_dispatcher_methods;

PaintDataDispatcher::PaintDataDispatcher(IConnection * conn) {
	_conn = conn;
	_data = conn->getPresetTemplate();
}

std::string PaintDataDispatcher::getPaintType() const { return cdm::getValue<std::string>(_data, PAINT_TYPE); }

void PaintDataDispatcher::setPaintType(std::string const & type) {
	if (_data.at(type) == AutoValue(type))
		return;

	_data[PAINT_TYPE] = type;
	_data.at(PAINT_CONSUMPTION).clear();
	_data.name().clear();
}

std::string PaintDataDispatcher::getMaterialType() const { return cdm::getValue<std::string>(_data, MATERIAL_TYPE); }

void PaintDataDispatcher::setMaterialType(std::string const & type) {
	if (_data.at(MATERIAL_TYPE) == AutoValue(type))
		return;

	_data[MATERIAL_TYPE] = type;
	_data.at(PAINT_CONSUMPTION);
	_data.name().clear();
}

double PaintDataDispatcher::getPaintConsumption() const {
	try {
		return cdm::getValue<double>(_data, PAINT_CONSUMPTION);
	} catch (UndefinedValueException const &) {
		// FIXME
		std::cerr << "coming soon\n";
		return 0;
		//return _conn->getPaintConsumption(getPaintType(), getMaterialType());
	}
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataDispatcher::setPaintConsumption(double value) {
	if (_data.at(PAINT_CONSUMPTION) == AutoValue(value))
		return;

	_data[PAINT_CONSUMPTION] = value;
	_data.at(PAINT_TYPE).clear();
	_data.at(MATERIAL_TYPE).clear();
	_data.name().clear();
}


double PaintDataDispatcher::getDivider() const { return cdm::getValue<double>(_data, DIVIDER); }
void PaintDataDispatcher::setDivider(double value) {
	if (_data.at(DIVIDER) == AutoValue(value))
		return;

	_data[DIVIDER] = value;
	_data.name().clear();
}

double PaintDataDispatcher::getPercentage() const { return cdm::getValue<double>(_data, PERCENTAGE); }
void PaintDataDispatcher::setPercentage(double value) {
	if (_data.at(PERCENTAGE) == AutoValue(value))
		return;

	_data[PERCENTAGE] = value;
	_data.name().clear();
}

double PaintDataDispatcher::getSheetWidth() const { return cdm::getValue<double>(_data, SHEET_WIDTH); }
void PaintDataDispatcher::setSheetWidth(double value) {
	if (_data.at(SHEET_WIDTH) == AutoValue(value))
		return;

	_data[SHEET_WIDTH] = value;
	_data.name().clear();
}

double PaintDataDispatcher::getSheetLength() const { return cdm::getValue<double>(_data, SHEET_LENGTH); }
void PaintDataDispatcher::setSheetLength(double value) {
	if ((double)_data.at(SHEET_LENGTH) == value)
		return;

	_data[SHEET_LENGTH] = value;
	_data.name().clear();
}

std::size_t PaintDataDispatcher::getCirculation() const { return cdm::getValue<std::size_t>(_data, CIRCULATION); }
void PaintDataDispatcher::setCirculation(std::size_t const & value) {
	if (_data.at(CIRCULATION) == AutoValue(value))
		return;

	_data[CIRCULATION] = value;
	_data.name().clear();
}

double PaintDataDispatcher::getPaintReserve() const { return cdm::getValue<double>(_data, PAINT_RESERVE); }
void PaintDataDispatcher::setPaintReserve(double value) {
	if (_data.at(PAINT_RESERVE) == AutoValue(value))
		return;

	_data[PAINT_RESERVE] = value;
	_data.name().clear();
}

double PaintDataDispatcher::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
