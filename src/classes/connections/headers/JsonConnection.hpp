#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include <fstream>
#include "IConnection.hpp"

class JsonConnection : public IConnection {
private:
	nlohmann::json _data;
	ConnectionStatus * _status;

	nlohmann::json getTable(std::string const &) const;

public:
	JsonConnection(nlohmann::json const &);
	JsonConnection(std::ifstream &);

	ConnectionStatus getStatus() const;

	// Queries for paint/material types table
	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getMaterialTypes() const;
	double getPaintConsumption(std::string const &, std::string const &) const;

	// Queires for paint presets
	std::vector<std::string> getPaintPresetsNames() const;
    std::vector<std::string> getPaintColumns() const;
	nlohmann::json getPaintPreset(std::string const &) const;
	nlohmann::json getPaintPresetTemplate() const;

	// Queries for lacquer presets
    std::vector<std::string> getLacquerPresetsNames() const;
    std::vector<std::string> getLacquerColumns() const;
    nlohmann::json getLacquerPreset(std::string const &) const;
	nlohmann::json getLacquerPresetTemplate() const;
};

#endif
