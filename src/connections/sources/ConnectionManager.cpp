#include <set>
#include <functional>

#include "ConnectionManager.hpp"

std::vector<std::string> getPresetNames(std::vector<IConnection *> const & connections, std::function<std::vector<std::string>(IConnection *)> getNames) {
	std::set<std::string> nameSet;
	for (auto conn : connections)
		for (auto name : getNames(conn))
			nameSet.insert(name);
	std::vector<std::string> res;
	for (auto name : nameSet)
		res.push_back(name);
	return res;
}


ConnectionManager::ConnectionManager(std::vector<IConnection *> const & connections) : _connections(connections) {}

int ConnectionManager::getStatus() const {
	for (auto conn : _connections)
		if (conn->getStatus())
			return conn->getStatus();
	return 0;
}

bool ConnectionManager::isReadOnly() const {
	for (auto conn : _connections)
		if (!conn->isReadOnly())
			return false;
	return true;
}

std::vector<std::string> ConnectionManager::getPaintTypes() const { return _connections.back()->getPaintTypes(); }
std::vector<std::string> ConnectionManager::getMaterialTypes() const { return _connections.back()->getMaterialTypes(); }
double ConnectionManager::getPaintConsumption(std::string const & paintType, std::string const & materialType) const { return _connections.back()->getPaintConsumption(paintType, materialType); }

std::vector<std::string> ConnectionManager::getPaintPresetNames() const {
	return getPresetNames(_connections, [](IConnection * conn) { return conn->getPaintPresetNames(); });
}
