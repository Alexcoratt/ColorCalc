#ifndef JSON_CONFIG_MANAGER_HPP
#define JSON_CONFIG_MANAGER_HPP

#include "IConfigManager.hpp"

class JSONConfigManager : public IConfigManager {
private:
	std::map<std::string, ITableConnection *> _connections;

public:
	JSONConfigManager(std::string const & configFileName);
	~JSONConfigManager();

	std::map<std::string, ITableConnection *> getConnections() const;
};

#endif
