#include <list>

#include <nlohmann/json.hpp>

#include <JSONConfigManager.hpp>
#include <JSONTableConnection.hpp>
#include <TableConnectionManager.hpp>

static std::list<ITableConnection *> releasedConnections;

class Source {
private:
	std::string _type;
	std::string _url;

public:
	Source() {}
	Source(std::string const & type, std::string const & url) : _type(type), _url(url) {}
	Source(Source const & other) : _type(other._type), _url(other._url) {}

	std::string getUrl() const { return _url; }
};

std::string getDir(std::string const & url) {
	if (!url.size())
		return "";

	std::size_t right = url.size();
	for (; right != 0 && url.at(right - 1) != '/'; --right);
	return url.substr(0, right);
}

struct TableConnectionData {
private:
	std::string _name;
	std::string _table;
	Source _data;
	Source _structure;
	bool _readOnly;

public:
	TableConnectionData(std::string const & name, std::string const & table, Source const & data, Source const & structure, bool readOnly) : _name(name), _table(table), _data(data), _structure(structure), _readOnly(readOnly) {}

	ITableConnection * getTableConnection(std::string const & baseDir) {
		return new JSONTableConnection{ baseDir + _structure.getUrl(), baseDir + _data.getUrl(), _table, _readOnly };
	}
};

std::map<std::string, Source> getSources(nlohmann::json const & sources) {
	std::map<std::string, Source> res;
	for (auto it = sources.begin(); it != sources.end(); ++it)
		res[it.key()] = Source{ it.value()["type"], it.value()["url"] };
	return res;
}

std::map<std::string, std::vector<TableConnectionData>> getConnectionData(nlohmann::json const & connections, std::map<std::string, Source> const & presetSources, std::map<std::string, Source> const & structureSources) {
	std::map<std::string, std::vector<TableConnectionData>> res;
	for (auto connectionIter = connections.begin(); connectionIter != connections.end(); ++connectionIter) {
		auto const & tables = connectionIter.value()["tables"];
		std::vector<TableConnectionData> tablesData;
		for (auto tableIter = tables.begin(); tableIter != tables.end(); ++tableIter) {
			auto const & table = tableIter.value();
			tablesData.push_back(
				TableConnectionData{ table["name"], table["table"], presetSources.at(table["source"]), structureSources.at(table["structure"]), table["read_only"] }
			);
		}
		res[connectionIter.key()] = tablesData;
	}
	return res;
}

std::map<std::string, ITableConnection *> getTableConnections(std::map<std::string, std::vector<TableConnectionData>> const & connectionData, std::string const & baseDir) {
	std::map<std::string, ITableConnection *> res;
	for (auto it = connectionData.begin(); it != connectionData.end(); ++it) {
		std::vector<ITableConnection *> conns;
		for (auto data : it->second) {
			ITableConnection * conn = data.getTableConnection(baseDir);
			conns.push_back(conn);
			releasedConnections.push_back(conn);
		}
		ITableConnection * connManager = new TableConnectionManager(conns);
		res[it->first] = connManager;
		conns.push_back(connManager);
		releasedConnections.push_back(connManager);
	}
	return res;
}

JSONConfigManager::JSONConfigManager(std::string const & configFileName) {
	std::ifstream confFile(configFileName);
	nlohmann::json const conf = nlohmann::json::parse(confFile);
	confFile.close();

	std::map<std::string, std::vector<TableConnectionData>> connectionData = getConnectionData(
		conf["connections"],
		getSources(conf["preset_sources"]),
		getSources(conf["structure_sources"])
	);

	_connections = getTableConnections(connectionData, getDir(configFileName));
}

JSONConfigManager::~JSONConfigManager() {
	while (!releasedConnections.empty()) {
		ITableConnection * conn = releasedConnections.front();
		releasedConnections.pop_front();
		delete conn;
	}
}

std::map<std::string, ITableConnection *> JSONConfigManager::getConnections() const { return _connections; }
