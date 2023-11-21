#include <array>
#include <iostream>

#include "FoilDataDispatcher.hpp"

#define CIRCULATION "circulation"
#define LENGTH "length"
#define WIDTH "width"
#define SHEET_NUMBER "sheet_number"
#define LENGTH_RESERVE "length_reserve"
#define WIDTH_RESERVE "width_reserve"

namespace cdm = common_dispatcher_methods;

FoilDataDispatcher::FoilDataDispatcher(IConnection * conn) {
	_conn = conn;
	_data = conn->getPresetTemplate();
}

std::size_t FoilDataDispatcher::getCirculation() const { return cdm::getValue<std::size_t>(_data, CIRCULATION); }
void FoilDataDispatcher::setCirculation(std::size_t const & value) {
	if (_data.at(CIRCULATION) == AutoValue(value))
		return;

	_data[CIRCULATION] = value;
	_data.name().clear();
}

double FoilDataDispatcher::getLength() const { return cdm::getValue<double>(_data, LENGTH); }
void FoilDataDispatcher::setLength(double value) {
	if (_data.at(LENGTH) == AutoValue(value))
		return;

	_data[LENGTH] = value;
	_data.name().clear();
}

double FoilDataDispatcher::getWidth() const { return cdm::getValue<double>(_data, WIDTH); }
void FoilDataDispatcher::setWidth(double value) {
	if (_data.at(WIDTH) == AutoValue(value))
		return;

	_data[WIDTH] = value;
	_data.name().clear();
}

std::size_t FoilDataDispatcher::getSheetNumber() const { return cdm::getValue<std::size_t>(_data, SHEET_NUMBER); }
void FoilDataDispatcher::setSheetNumber(std::size_t const & value) {
	if (_data.at(SHEET_NUMBER) == AutoValue(value))
		return;

	_data[SHEET_NUMBER] = value;
	_data.name().clear();
}

double FoilDataDispatcher::getLengthReserve() const { return cdm::getValue<double>(_data, LENGTH_RESERVE); }
void FoilDataDispatcher::setLengthReserve(double value) {
	if (_data.at(LENGTH_RESERVE) == AutoValue(value))
		return;

	_data[LENGTH_RESERVE] = value;
	_data.name().clear();
}

double FoilDataDispatcher::getWidthReserve() const { return cdm::getValue<double>(_data, WIDTH_RESERVE); }
void FoilDataDispatcher::setWidthReserve(double value) {
	if ((double)_data.at(WIDTH_RESERVE) == value)
		return;

	_data[WIDTH_RESERVE] = value;
	_data.name().clear();
}

std::vector<std::string> FoilDataDispatcher::getSuitableFoilRolls() const {
	// FIXME
	std::cerr << "coming soon\n";
	return {};
}

double FoilDataDispatcher::calculate() const { return (getLength() + getLengthReserve()) * getCirculation() / getSheetNumber() / 1000; }
