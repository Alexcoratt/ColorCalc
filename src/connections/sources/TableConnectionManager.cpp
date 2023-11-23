#include <set>

#include "TableConnectionManager.hpp"

#include "PresetDoesNotExistException.hpp"
#include "PresetAlreadyExistsException.hpp"

TableConnectionManager::TableConnectionManager(std::vector<ITableConnection *> const & connections) : _connections(connections) {}

int TableConnectionManager::getStatus() const {
	for (auto const * conn : _connections)
		if (!conn->getStatus())
			return conn->getStatus();
	return 0;
}

bool TableConnectionManager::isReadOnly() const {
	for (auto const * conn : _connections)
		if (!conn->isReadOnly())
			return false;
	return true;
}

std::vector<std::string> TableConnectionManager::getParamNames() const {
	return _connections.back()->getParamNames();
}

std::vector<std::string> TableConnectionManager::getPresetNames() const {
	std::set<std::string> names;
	for (auto const * conn : _connections)
		for (auto name : conn->getPresetNames())
			names.insert(name);

	return {names.begin(), names.end()};
}

// FIXME: this method must translate the certain connection's param names
// into actual param names
// (returning by TableConnectionManager::getParamNames())
std::map<std::string, AutoValue> TableConnectionManager::getPreset(std::string const & name) const {
	for (auto it = _connections.rbegin(); it != _connections.rend(); ++it)
		try {
			return (*it)->getPreset(name);
		} catch (PresetDoesNotExistException const &) {}

	throw PresetDoesNotExistException(name);
}

void TableConnectionManager::createPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	if (hasPreset(name))
		throw PresetAlreadyExistsException(name);

	for (auto it = _connections.rbegin(); it != _connections.rend(); ++it)
		if (!(*it)->isReadOnly()) {
			(*it)->createPreset(name, params);
			return;
		}

	_connections.back()->createPreset(name, params);
}

void TableConnectionManager::updatePreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	for (auto it = _connections.rbegin(); it != _connections.rend(); ++it)
		try {
			(*it)->updatePreset(name, params);
			return;
		} catch (PresetDoesNotExistException const &) {}

	throw PresetDoesNotExistException(name);
}

void TableConnectionManager::removePreset(std::string const & name) {
	for (auto it = _connections.rbegin(); it != _connections.rend(); ++it)
		try {
			(*it)->removePreset(name);
			return;
		} catch (PresetDoesNotExistException const &) {}

	throw PresetDoesNotExistException(name);
}
