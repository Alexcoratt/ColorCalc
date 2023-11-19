#include <stdexcept>

#include "LacquerDataDispatcher.hpp"

#define PERCENTAGE "percentage"
#define LACQUER_CONSUMPTION "lacquer_consumption"
#define SHEET_LENGTH "sheet_length"
#define SHEET_WIDTH "sheet_width"
#define CIRCULATION "circulation"

namespace cdm = common_dispatcher_methods;

LacquerDataDispatcher::LacquerDataDispatcher(IConnection * conn) {
	_conn = conn;
	_data = conn->getPresetTemplate();
}

double LacquerDataDispatcher::getPercentage() const { return cdm::getValue<double>(_data, PERCENTAGE); }
void LacquerDataDispatcher::setPercentage(double value) {
	if (_data.at(PERCENTAGE) == AutoValue(value))
		return;

	_data[PERCENTAGE] = value;
	_data.name().clear();
}

double LacquerDataDispatcher::getLacquerConsumption() const { return cdm::getValue<double>(_data, LACQUER_CONSUMPTION); }
void LacquerDataDispatcher::setLacquerConsumption(double value) {
	if (_data.at(LACQUER_CONSUMPTION) == AutoValue(value))
		return;

	_data[LACQUER_CONSUMPTION] = value;
	_data.name().clear();
}

double LacquerDataDispatcher::getSheetLength() const { return cdm::getValue<double>(_data, SHEET_LENGTH); }
void LacquerDataDispatcher::setSheetLength(double value) {
	if (_data.at(SHEET_LENGTH) == AutoValue(value))
		return;

	_data[SHEET_LENGTH] = value;
	_data.name().clear();
}

double LacquerDataDispatcher::getSheetWidth() const { return cdm::getValue<double>(_data, SHEET_WIDTH); }
void LacquerDataDispatcher::setSheetWidth(double value) {
	if (_data.at(SHEET_WIDTH) == AutoValue(value))
		return;

	_data[SHEET_WIDTH] = value;
	_data.name().clear();
}

std::size_t LacquerDataDispatcher::getCirculation() const { return cdm::getValue<std::size_t>(_data, CIRCULATION); }
void LacquerDataDispatcher::setCirculation(std::size_t value) {
	if ((std::size_t)_data.at(CIRCULATION) == value)
		return;

	_data[CIRCULATION] = value;
	_data.name().clear();
}

double LacquerDataDispatcher::calculate() const {
	return getSheetLength() * getSheetWidth() / 1000000 * getLacquerConsumption() / 1000 * getCirculation() * getPercentage() / 100;
}
