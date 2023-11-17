#include "FoilDataDispatcher.hpp"

#define CIRCULATION "circulation"
#define LENGTH "length"
#define SHEET_NUMBER "sheet_number"
#define RESERVE "reserve"

FoilDataDispatcher::FoilDataDispatcher(IConnection * conn) : _conn(conn), _params(conn->getFoilPresetTemplate()) {}

IConnection * FoilDataDispatcher::getConnection() const { return _conn; }

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

std::string FoilDataDispatcher::getPresetName() const { return _presetName; }
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
}

void FoilDataDispatcher::createPreset(std::string const & name) { _conn->createFoilPreset(name, _params); }
void FoilDataDispatcher::updatePreset(std::string const & name) { _conn->updateFoilPreset(name, _params); }
void FoilDataDispatcher::removePreset(std::string const & name) { _conn->removeFoilPreset(name); }

std::size_t FoilDataDispatcher::getCirculation() const { return _params.at(CIRCULATION); }
void FoilDataDispatcher::setCirculation(std::size_t const & value) { _params[CIRCULATION] = value; }

double FoilDataDispatcher::getLength() const { return _params.at(LENGTH); }
void FoilDataDispatcher::setLength(double value) { _params[LENGTH] = value; }

std::size_t FoilDataDispatcher::getSheetNumber() const { return _params.at(SHEET_NUMBER); }
void FoilDataDispatcher::setSheetNumber(std::size_t const & value) { _params[SHEET_NUMBER] = value; }

double FoilDataDispatcher::getReserve() const { return _params.at(RESERVE); }
void FoilDataDispatcher::setReserve(double value) { _params[RESERVE] = value; }

double FoilDataDispatcher::calculate() const { return (getLength() + getReserve()) * getCirculation() / getSheetNumber() / 1000; }
