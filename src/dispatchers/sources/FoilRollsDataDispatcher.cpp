#include "FoilRollsDataDispatcher.hpp"

#define LENGTH "length"
#define WIDTH "width"

namespace ccm = common_container_methods;

FoilRollsDataDispatcher::FoilRollsDataDispatcher(IConnection * conn) : _conn(conn), _params(conn->getFoilRollPresetTemplate()) {}

IConnection * FoilRollsDataDispatcher::getConnection() { return _conn; }

std::vector<std::string> FoilRollsDataDispatcher::getAvailablePresetNames() const { return _conn->getFoilRollPresetNames(); }
std::vector<std::string> FoilRollsDataDispatcher::getParamNames() const {
	std::vector<std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.push_back(it->first);
	return res;
}

std::map<std::string, std::string> FoilRollsDataDispatcher::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto it = _params.begin(); it != _params.end(); ++it)
		res.insert({it->first, it->second});
	return res;
}

void FoilRollsDataDispatcher::clear() {
	for (auto it = _params.begin(); it != _params.end(); ++it)
		it->second.clear();
	_presetName.clear();
}

std::string FoilRollsDataDispatcher::getPresetName() const { return _presetName; }

void FoilRollsDataDispatcher::setPreset(std::string const & name) {
	auto preset = _conn->getFoilRollPreset(name);

	if (!preset.at(LENGTH).isNull())
		_params[LENGTH] = preset.at(LENGTH);
	if (!preset.at(WIDTH).isNull())
		_params[WIDTH] = preset.at(WIDTH);

	_presetName = name;
}

void FoilRollsDataDispatcher::createPreset(std::string const & name) {
	_conn->createFoilRollPreset(name, _params);
	_presetName = name;
}

void FoilRollsDataDispatcher::updatePreset(std::string const & name) { _conn->updateFoilRollPreset(name, _params); }
void FoilRollsDataDispatcher::removePreset(std::string const & name) { _conn->removeFoilRollPreset(name); }

double FoilRollsDataDispatcher::calculate() const { throw std::runtime_error("FoilRollDataDispatcher does no calculations"); }

double FoilRollsDataDispatcher::getLength() const { return ccm::getParam(_params, LENGTH); }

void FoilRollsDataDispatcher::setLength(double value) {
	if (_params.at(LENGTH) == AutoValue(value))
		return;

	_params[LENGTH] = value;
	_presetName.clear();
}

double FoilRollsDataDispatcher::getWidth() const { return ccm::getParam(_params, WIDTH); }

void FoilRollsDataDispatcher::setWidth(double value) {
	if (_params.at(WIDTH) == AutoValue(value))
		return;

	_params[WIDTH] = value;
	_presetName.clear();
}
