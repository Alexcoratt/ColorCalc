#include <list>

#include <json/json.h>

#include <JSONConfigManager.hpp>
#include <JSONTableConnection.hpp>
#include <TableConnectionManager.hpp>
#include <auxillary_methods.hpp>

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

struct TableConnectionData {
private:
	std::string _name;
	std::string _table;
	Source _data;
	Source _structure;
	bool _readOnly;

public:
	TableConnectionData(std::string const & name, std::string const & table, Source const & data, Source const & structure, bool readOnly) : _name(name), _table(table), _data(data), _structure(structure), _readOnly(readOnly) {}

	ITableConnection * getTableConnection(std::string const & baseDir, bool quiet) {
		return new JSONTableConnection{ baseDir + _structure.getUrl(), baseDir + _data.getUrl(), _table, _readOnly, quiet };
	}
};

Json::Value getJsonValue(Json::Value const & value, char const * key, Json::Value defaultValue = Json::nullValue) { return value.get(key, defaultValue); }

Json::Value getJsonValue(Json::ValueIterator const & iter, char const * key, Json::Value defaultValue = Json::nullValue) { return iter->get(key, defaultValue); }

Json::Value getJsonValue(Json::ValueConstIterator const & iter, char const * key, Json::Value defaultValue = Json::nullValue) { return iter->get(key, defaultValue); }

std::map<std::string, Source> getSources(Json::Value const & sources) {
	std::map<std::string, Source> res;
	for (auto it = sources.begin(); it != sources.end(); ++it) {
		res[it.key().asString()] = Source{ getJsonValue(it, "type").asString(), getJsonValue(it, "url").asString() };
	}
	return res;
}

std::map<std::string, std::vector<TableConnectionData>> getConnectionData(Json::Value const & connections, std::map<std::string, Source> const & presetSources, std::map<std::string, Source> const & structureSources) {
	std::map<std::string, std::vector<TableConnectionData>> res;
	for (auto connectionIter = connections.begin(); connectionIter != connections.end(); ++connectionIter) {
		auto const & tables = connectionIter->get("tables", Json::nullValue);
		std::vector<TableConnectionData> tablesData;
		for (auto tableIter = tables.begin(); tableIter != tables.end(); ++tableIter) {
			tablesData.push_back(
				TableConnectionData{
					getJsonValue(tableIter, "name").asString(),
					getJsonValue(tableIter, "table").asString(),
					presetSources.at(getJsonValue(tableIter, "source").asString()),
					structureSources.at(getJsonValue(tableIter, "structure").asString()),
					getJsonValue(tableIter, "read_only").asBool()
				}
			);
		}
		res[connectionIter.key().asString()] = tablesData;
	}
	return res;
}

std::map<std::string, ITableConnection *> getTableConnections(std::map<std::string, std::vector<TableConnectionData>> const & connectionData, std::string const & baseDir, bool quiet) {
	std::map<std::string, ITableConnection *> res;
	for (auto it = connectionData.begin(); it != connectionData.end(); ++it) {
		std::vector<ITableConnection *> conns;
		for (auto data : it->second) {
			ITableConnection * conn = data.getTableConnection(baseDir, quiet);
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

JSONConfigManager::JSONConfigManager(std::string const & configFileName, bool quiet) {
	std::ifstream confFile(configFileName);
	Json::Value conf;
	confFile >> conf;
	//nlohmann::json const conf = nlohmann::json::parse(confFile);
	confFile.close();

	std::map<std::string, std::vector<TableConnectionData>> connectionData = getConnectionData(
		conf["connections"],
		getSources(conf["preset_sources"]),
		getSources(conf["structure_sources"])
	);

	_connections = getTableConnections(connectionData, auxillary_methods::getDir(configFileName), quiet);
}

JSONConfigManager::~JSONConfigManager() {
	while (!releasedConnections.empty()) {
		ITableConnection * conn = releasedConnections.front();
		releasedConnections.pop_front();
		delete conn;
	}
}

std::map<std::string, ITableConnection *> JSONConfigManager::getConnections() const { return _connections; }
