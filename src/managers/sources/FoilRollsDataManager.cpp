#include "FoilRollsDataManager.hpp"
#include "auxillary_methods.hpp"

#define LENGTH "length"
#define WIDTH "width"

FoilRollsDataManager::FoilRollsDataManager(ITableConnection * conn) {
	setConnection(conn);
	importData(conn->getPresetTemplate());
}

void FoilRollsDataManager::importData(std::map<std::string, AutoValue> const & params) {
	auxillary_methods::setParam(_length, params, LENGTH);
	auxillary_methods::setParam(_width, params, WIDTH);
}

std::map<std::string, AutoValue> FoilRollsDataManager::exportData() const {
	std::map<std::string, AutoValue> res;
	auxillary_methods::setMapValue(res, _length);
	auxillary_methods::setMapValue(res, _width);
	return res;
}

void FoilRollsDataManager::clear() {
	clearName();
	_length.clear();
	_width.clear();
}

void FoilRollsDataManager::setName(std::string const & name) { _name = name; }
void FoilRollsDataManager::clearName() { _name.clear(); }
std::string FoilRollsDataManager::getName() const { return _name; }

double FoilRollsDataManager::calculate() const { throw std::runtime_error("FoilRollDataDispatcher does no calculations"); }

double FoilRollsDataManager::getLength() const { return _length; }
void FoilRollsDataManager::setLength(double value) {
	if (_length == value)
		return;

	_length = value;
	clearName();
}

double FoilRollsDataManager::getWidth() const { return _width; }
void FoilRollsDataManager::setWidth(double value) {
	if (_width == value)
		return;

	_width = value;
	clearName();
}
