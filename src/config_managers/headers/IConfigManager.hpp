#ifndef I_CONFIG_MANAGER_HPP
#define I_CONFIG_MANAGER_HPP

#include <string>
#include <map>

#include "ITableConnection.hpp"

class IConfigManager {
public:
	virtual ~IConfigManager() {}

	virtual std::map<std::string, ITableConnection *> getConnections() const = 0;
};

#endif
