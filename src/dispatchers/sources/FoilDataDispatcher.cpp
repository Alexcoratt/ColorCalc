#include "FoilDataDispatcher.hpp"

#define CIRCULATION "circulation"
#define LENGTH "length"
#define SHEET_NUMBER "sheet_number"
#define WIDTH_RESERVE "width_reserve"

namespace ccm = common_container_methods;

FoilDataDispatcher::FoilDataDispatcher(IConnection * conn) : _conn(conn), _params(conn->getFoilPresetTemplate()) {}

IConnection * FoilDataDispatcher::getConnection() const { return _conn; }

std::vector<std::string> FoilDataDispatcher::getAvailablePresetNames() const { return _conn->getFoilPresetNames(); }

std::vector<std::string> FoilDataDispatcher::getParamNames() const { return _conn->getFoilPresetColumns(); }

std::map<std::string, std::string> FoilDataDispatcher::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.insert({it->first, it->second});
	return res;
}

void FoilDataDispatcher::clear() {
	for (auto it = _params.begin(); it != _params.end(); ++it)
		it->second.clear();
	_presetName.clear();
}

std::string FoilDataDispatcher::getPresetName() const {
	if (_presetName.empty())
		throw UndefinedValueException("preset name");
	return _presetName;
}

void FoilDataDispatcher::setPreset(std::string const & name) {
	if (_presetName == name)
		return;

	auto params = _conn->getFoilPreset(name);

	if (!params.at(CIRCULATION).isNull())
		_params[CIRCULATION] = std::stoul(params.at(CIRCULATION));
	if (!params.at(LENGTH).isNull())
		_params[LENGTH] = std::stod(params.at(LENGTH));
	if (!params.at(SHEET_NUMBER).isNull())
		_params[SHEET_NUMBER] = std::stoul(params.at(SHEET_NUMBER));
	if (!params.at(WIDTH_RESERVE).isNull())
		_params[WIDTH_RESERVE] = std::stod(params.at(WIDTH_RESERVE));

	_presetName = name;
}

void FoilDataDispatcher::createPreset(std::string const & name) { _conn->createFoilPreset(name, _params); }
void FoilDataDispatcher::updatePreset(std::string const & name) { _conn->updateFoilPreset(name, _params); }
void FoilDataDispatcher::removePreset(std::string const & name) { _conn->removeFoilPreset(name); }

std::size_t FoilDataDispatcher::getCirculation() const { return ccm::getParam(_params, CIRCULATION); }
void FoilDataDispatcher::setCirculation(std::size_t const & value) {
	if ((std::size_t)_params.at(CIRCULATION) == value)
		return;

	_params[CIRCULATION] = value;
	_presetName.clear();
}

double FoilDataDispatcher::getLength() const { return ccm::getParam(_params, LENGTH); }
void FoilDataDispatcher::setLength(double value) {
	if ((double)_params.at(LENGTH) == value)
		return;

	_params[LENGTH] = value;
	_presetName.clear();
}

std::size_t FoilDataDispatcher::getSheetNumber() const { return ccm::getParam(_params, SHEET_NUMBER); }
void FoilDataDispatcher::setSheetNumber(std::size_t const & value) {
	if ((std::size_t)_params.at(SHEET_NUMBER) == value)
		return;

	_params[SHEET_NUMBER] = value;
	_presetName.clear();
}

double FoilDataDispatcher::getWidthReserve() const { return ccm::getParam(_params, WIDTH_RESERVE); }
void FoilDataDispatcher::setWidthReserve(double value) {
	if ((double)_params.at(WIDTH_RESERVE) == value)
		return;

	_params[WIDTH_RESERVE] = value;
	_presetName.clear();
}

double FoilDataDispatcher::calculate() const { return (getLength() + getWidthReserve()) * getCirculation() / getSheetNumber() / 1000; }
