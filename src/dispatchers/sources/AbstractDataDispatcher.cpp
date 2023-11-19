#include "AbstractDataDispatcher.hpp"
#include "UndefinedValueException.hpp"

IConnection * AbstractDataDispatcher::getConnection() { return _conn; }

std::vector<std::string> AbstractDataDispatcher::getAvailablePresetNames() const { return _conn->getPresetNames(); }

std::vector<std::string> AbstractDataDispatcher::getParamNames() const { return _conn->getPresetParamNames(); }

std::map<std::string, std::string> AbstractDataDispatcher::toStringMap() const {
	std::map<std::string, std::string> res;
	for (auto iter = _data.begin(); iter != _data.end(); ++iter)
		res[iter->first] = (std::string)iter->second;

	return res;
}

void AbstractDataDispatcher::clear() { _data = _conn->getPresetTemplate(); }

std::string AbstractDataDispatcher::getPresetName() const {
	auto const & name = _data.name();
	if (name.isNull())
		throw UndefinedValueException("name");
	return name;
}

void AbstractDataDispatcher::setPreset(std::string const & name) {
	if (_data.name() == AutoValue(name))
		return;

	_data = _conn->getPreset(name);
}

void AbstractDataDispatcher::createPreset(std::string const & name) {
	_data.name() = name;
	_conn->createPreset(_data);
}

void AbstractDataDispatcher::updatePreset(std::string const & name) {
	_data.name() = name;
	_conn->updatePreset(_data);
}

void AbstractDataDispatcher::removePreset(std::string const & name) {
	_conn->removePreset(name);
}
