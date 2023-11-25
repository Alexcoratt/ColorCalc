#ifndef BASE_CONFIG_MANAGER_HPP
#define BASE_CONFIG_MANAGER_HPP

#include <fstream>
#include <string>
#include <map>

class BaseConfigManager {
private:
	std::map<std::string, std::string> _params;

public:
	BaseConfigManager(std::string const & filename);

	bool getQuiet() const;
	std::string getConfigFileName() const;
	std::string getPlatform() const;
};

inline BaseConfigManager::BaseConfigManager(std::string const & filename) {
	std::ifstream file(filename);

	if (file.fail()) {
		file.close();
		throw std::runtime_error("Critical error: Base config file is not found");
	}

	while(!file.eof()) {
		std::string key;
		std::string value;
		std::getline(file, key, '=');
		std::getline(file, value);
		_params[key] = value;
	}
	file.close();
}

inline bool BaseConfigManager::getQuiet() const {
	try {
		return _params.at("quiet") == "true";
	} catch (std::out_of_range const &) {
		return true;
	}
}

inline std::string BaseConfigManager::getConfigFileName() const {
	return _params.at("config_file");
}

inline std::string BaseConfigManager::getPlatform() const {
	try {
		return _params.at("platform");
	} catch (std::out_of_range const &) {
		return "linux";
	}
}

#endif
