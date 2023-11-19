#include "FoilRollsDataDispatcher.hpp"

#define LENGTH "length"
#define WIDTH "width"

namespace cdm = common_dispatcher_methods;

FoilRollsDataDispatcher::FoilRollsDataDispatcher(IConnection * conn) {
	_conn = conn;
	_data = conn->getPresetTemplate();
}

double FoilRollsDataDispatcher::calculate() const { throw std::runtime_error("FoilRollDataDispatcher does no calculations"); }

double FoilRollsDataDispatcher::getLength() const { return cdm::getValue<double>(_data, LENGTH); }

void FoilRollsDataDispatcher::setLength(double value) {
	if (_data.at(LENGTH) == AutoValue(value))
		return;

	_data[LENGTH] = value;
	_data.name().clear();
}

double FoilRollsDataDispatcher::getWidth() const { return cdm::getValue<double>(_data, WIDTH); }

void FoilRollsDataDispatcher::setWidth(double value) {
	if (_data.at(WIDTH) == AutoValue(value))
		return;

	_data[WIDTH] = value;
	_data.name().clear();
}
