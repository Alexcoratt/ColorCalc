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
	_paintConsumptionManager = paintConsumptionDispatcher;
	_name.setName("preset name");
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
	_name.clear();
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

std::vector<std::string> PaintDataManager::getPaintTypes() const { return _paintConsumptionManager->getPaintTypes(); }
std::vector<std::string> PaintDataManager::getMaterialTypes() const { return _paintConsumptionManager->getMaterialTypes(); }

std::string PaintDataManager::getPaintType() const { return _paintType; }

void PaintDataManager::setPaintType(std::string const & type) {
	if (_paintType == type)
		return;

	_paintType = type;
	_paintConsumption.clear();
	_name.clear();
}

void PaintDataManager::clearPaintType() {
	if (!_paintType.isDefined())
		return;

	_paintType.clear();
	_paintConsumption.clear();
	_name.clear();
}

std::string PaintDataManager::getMaterialType() const { return _materialType; }

void PaintDataManager::setMaterialType(std::string const & type) {
	if (_materialType == type)
		return;

	_materialType = type;
	_paintConsumption.clear();
	_name.clear();
}

void PaintDataManager::clearMaterialType() {
	if (!_materialType.isDefined())
		return;

	_materialType.clear();
	_paintConsumption.clear();
	_name.clear();
}

double PaintDataManager::getPaintConsumption() const {
	try {
		return _paintConsumptionManager->getPaintConsumption(getPaintType(), getMaterialType());
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
	_name.clear();
}

void PaintDataManager::clearPaintConsumption() {
	if (!_paintConsumption.isDefined())
		return;

	_paintConsumption.clear();
	_paintType.clear();
	_materialType.clear();
	_name.clear();
}

double PaintDataManager::getDivider() const { return _divider; }
void PaintDataManager::setDivider(double value) {
	if (_divider == value)
		return;

	_divider = value;
	_name.clear();
}

void PaintDataManager::clearDivider() {
	if (!_divider.isDefined())
		return;

	_divider.clear();
	_name.clear();
}

double PaintDataManager::getPercentage() const { return _percentage; }
void PaintDataManager::setPercentage(double value) {
	if (_percentage == value)
		return;

	_percentage = value;
	_name.clear();
}

void PaintDataManager::clearPercentage() {
	if (!_percentage.isDefined())
		return;

	_percentage.clear();
	_name.clear();
}

double PaintDataManager::getSheetWidth() const { return _sheetWidth; }
void PaintDataManager::setSheetWidth(double value) {
	if (_sheetWidth == value)
		return;

	_sheetWidth = value;
	_name.clear();
}

void PaintDataManager::clearSheetWidth() {
	if (!_sheetWidth.isDefined())
		return;

	_sheetWidth.clear();
	_name.clear();
}

double PaintDataManager::getSheetLength() const { return _sheetLength; }
void PaintDataManager::setSheetLength(double value) {
	if (_sheetLength == value)
		return;

	_sheetLength = value;
	_name.clear();
}

void PaintDataManager::clearSheetLength() {
	if (!_sheetLength.isDefined())
		return;

	_sheetLength.clear();
	_name.clear();
}

unsigned long PaintDataManager::getCirculation() const { return _circulation; }
void PaintDataManager::setCirculation(unsigned long const & value) {
	if (_circulation == value)
		return;

	_circulation = value;
	_name.clear();
}

void PaintDataManager::clearCirculation() {
	if (!_circulation.isDefined())
		return;

	_circulation.clear();
	_name.clear();
}

double PaintDataManager::getPaintReserve() const { return _paintReserve; }
void PaintDataManager::setPaintReserve(double value) {
	if (_paintReserve == value)
		return;

	_paintReserve = value;
	_name.clear();
}

void PaintDataManager::clearPaintReserve() {
	if (!_paintReserve.isDefined())
		return;

	_paintReserve.clear();
	_name.clear();
}

double PaintDataManager::calculate() const {
	return getSheetWidth() * getSheetLength() / 1000000 * getPaintConsumption() / 1000 / getDivider() * getCirculation() * getPercentage() / 100 + getPaintReserve();
}
