#include <cstddef>
#include <iostream>

#include "PaintDataManager.hpp"
#include "PaintConsumptionDataManager.hpp"
#include "auxillary_methods.hpp"

#define PAINT_TYPE "paint_type"
#define MATERIAL_TYPE "material_type"
#define PAINT_CONSUMPTION "paint_consumption"
#define DIVIDER "divider"
#define PERCENTAGE "percentage"
#define SHEET_WIDTH "sheet_width"
#define SHEET_LENGTH "sheet_length"
#define CIRCULATION "circulation"
#define PAINT_RESERVE "paint_reserve"

PaintDataManager::PaintDataManager(ITableConnection * conn, PaintConsumptionDataManager const * paintConsumptionDispatcher) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
	_paintConsumptionDispatcher = paintConsumptionDispatcher;
}

void PaintDataManager::importData(std::map<std::string, AutoValue> const & params) {
	auxillary_methods::setParam(_paintType, params, PAINT_TYPE);
	auxillary_methods::setParam(_materialType, params, MATERIAL_TYPE);
	auxillary_methods::setParam(_paintConsumption, params, PAINT_CONSUMPTION);
	auxillary_methods::setParam(_divider, params, DIVIDER);
	auxillary_methods::setParam(_percentage, params, PERCENTAGE);
	auxillary_methods::setParam(_sheetWidth, params, SHEET_WIDTH);
	auxillary_methods::setParam(_sheetLength, params, SHEET_LENGTH);
	auxillary_methods::setParam(_circulation, params, CIRCULATION);
	auxillary_methods::setParam(_paintReserve, params, PAINT_RESERVE);
}

std::map<std::string, AutoValue> PaintDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	auxillary_methods::setMapValue(res, _paintType);
	auxillary_methods::setMapValue(res, _materialType);

	try {
		res[_paintConsumption.getName()] = getPaintConsumption();
	} catch (UndefinedValueException const &) {
		res[_paintConsumption.getName()];
	}

	auxillary_methods::setMapValue(res, _divider);
	auxillary_methods::setMapValue(res, _percentage);
	auxillary_methods::setMapValue(res, _sheetWidth);
	auxillary_methods::setMapValue(res, _sheetLength);
	auxillary_methods::setMapValue(res, _circulation);
	auxillary_methods::setMapValue(res, _paintReserve);
	return res;
}

void PaintDataManager::clear() {
	clearName();
	_paintType.clear();
	_materialType.clear();
	_paintConsumption.clear();
	_divider.clear();
	_percentage.clear();
	_sheetWidth.clear();
	_sheetLength.clear();
	_circulation.clear();
	_paintReserve.clear();
}

void PaintDataManager::setName(std::string const & name) { _name = name; }
void PaintDataManager::clearName() { _name.clear(); }
std::string PaintDataManager::getName() const { return _name; }

std::vector<std::string> PaintDataManager::getPaintTypes() const { return _paintConsumptionDispatcher->getPaintTypes(); }
std::vector<std::string> PaintDataManager::getMaterialTypes() const { return _paintConsumptionDispatcher->getMaterialTypes(); }

std::string PaintDataManager::getPaintType() const { return _paintType; }

void PaintDataManager::setPaintType(std::string const & type) {
	if (_paintType == type)
		return;

	_paintType = type;
	_paintConsumption.clear();
	clearName();
}

std::string PaintDataManager::getMaterialType() const { return _materialType; }

void PaintDataManager::setMaterialType(std::string const & type) {
	if (_materialType == type)
		return;

	_materialType = type;
	_paintConsumption.clear();
	clearName();
}

double PaintDataManager::getPaintConsumption() const {
	try {
		return _paintConsumptionDispatcher->getPaintConsumption(getPaintType(), getMaterialType());
	} catch (UndefinedValueException const &) {
		return _paintConsumption;
	}
}

// In case paint consumption value was successfully updated, clears paint type and material type data
void PaintDataManager::setPaintConsumption(double value) {
	if (_paintConsumption == value)
		return;

	_paintConsumption = value;
	_paintType.clear();
	_materialType.clear();
	clearName();
}


double PaintDataManager::getDivider() const { return _divider; }
void PaintDataManager::setDivider(double value) {
	if (_divider == value)
		return;

	_divider = value;
	clearName();
}

double PaintDataManager::getPercentage() const { return _percentage; }
void PaintDataManager::setPercentage(double value) {
	if (_percentage == value)
		return;

	_percentage = value;
	clearName();
}

double PaintDataManager::getSheetWidth() const { return _sheetWidth; }
void PaintDataManager::setSheetWidth(double value) {
	if (_sheetWidth == value)
		return;

	_sheetWidth = value;
	clearName();
}

double PaintDataManager::getSheetLength() const { return _sheetLength; }
void PaintDataManager::setSheetLength(double value) {
	if (_sheetLength == value)
		return;

	_sheetLength = value;
	clearName();
}

std::size_t PaintDataManager::getCirculation() const { return _circulation; }
void PaintDataManager::setCirculation(std::size_t const & value) {
	if (_circulation == value)
		return;

	_circulation = value;
	clearName();
}

double PaintDataManager::getPaintReserve() const { return _paintReserve; }
void PaintDataManager::setPaintReserve(double value) {
	if (_paintReserve == value)
		return;

	_paintReserve = value;
	clearName();
}

double PaintDataManager::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
