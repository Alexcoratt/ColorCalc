#include "PaintDataContainer.hpp"

#define CONTAINER_NAME "name"
#define PAINT_TYPE "paint_type"
#define MATERIAL_TYPE "material_type"
#define PAINT_CONSUMPTION "paint_consumption"
#define DIVIDER "divider"
#define PERCENTAGE "percentage"
#define SHEET_WIDTH "sheet_width"
#define SHEET_LENGTH "sheet_length"
#define CIRCULATION "circulation"
#define PAINT_RESERVE "paint_reserve"

PaintDataContainer::PaintDataContainer(std::map<std::string, AutoValue> const & data) :
_name(CONTAINER_NAME),
_paintType(PAINT_TYPE),
_materialType(MATERIAL_TYPE),
_paintConsumption(PAINT_CONSUMPTION),
_divider(DIVIDER),
_percentage(PERCENTAGE),
_sheetWidth(SHEET_WIDTH),
_sheetLength(SHEET_LENGTH),
_circulation(CIRCULATION),
_paintReserve(PAINT_RESERVE) {
	importData(data);
}

std::map<std::string, AutoValue> PaintDataContainer::exportData() const {
	return {
		{_paintType.getName(), _paintType.getValue()},
		{_materialType.getName(), _materialType.getValue()},
		{_paintConsumption.getName(), _paintConsumption.getValue()},
		{_divider.getName(), _divider.getValue()},
		{_percentage.getName(), _percentage.getValue()},
		{_sheetWidth.getName(), _sheetWidth.getValue()},
		{_sheetLength.getName(), _sheetLength.getValue()},
		{_circulation.getName(), _circulation.getValue()},
		{_paintReserve.getName(), _paintReserve.getValue()},
	};
}

void PaintDataContainer::importData(std::map<std::string, AutoValue> const & data) {
	_paintType.setValue(data.at(PAINT_TYPE));
	_materialType.setValue(data.at(MATERIAL_TYPE));
	_paintConsumption.setValue(data.at(MATERIAL_TYPE));
	_divider.setValue(data.at(DIVIDER));
	_percentage.setValue(data.at(PERCENTAGE));
	_sheetWidth.setValue(data.at(SHEET_WIDTH));
	_sheetLength.setValue(data.at(SHEET_LENGTH));
	_circulation.setValue(data.at(CIRCULATION));
	_paintReserve.setValue(data.at(PAINT_RESERVE));
}

void PaintDataContainer::clear() {
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

std::string PaintDataContainer::getName() const { return _name; }
void PaintDataContainer::setName(std::string const & name) { _name = name; }

std::string PaintDataContainer::getPaintType() const { return _paintType; }
void PaintDataContainer::setPaintType(std::string const & type) { _paintType = type; }

std::string PaintDataContainer::getMaterialType() const { return _materialType; }
void PaintDataContainer::setMaterialType(std::string const & type) { _materialType = type; }

double PaintDataContainer::getPaintConsumption() const { return _paintConsumption; }
void PaintDataContainer::setPaintConsumption(double value) { _paintConsumption = value; }

double PaintDataContainer::getDivider() const { return _divider; }
void PaintDataContainer::setDivider(double value) { _divider = value; }

double PaintDataContainer::getPercentage() const { return _percentage; }
void PaintDataContainer::setPercentage(double value) { _percentage = value; }

double PaintDataContainer::getSheetWidth() const { return _sheetWidth; }
void PaintDataContainer::setSheetWidth(double value) { _sheetWidth = value; }

double PaintDataContainer::getSheetLength() const;
void PaintDataContainer::setSheetLength(double);

unsigned long PaintDataContainer::getCirculation() const;
void PaintDataContainer::setCirculation(unsigned long);

double PaintDataContainer::getPaintReserve() const;
void PaintDataContainer::setPaintReserve(double);
