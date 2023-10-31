#ifndef I_CONNECTION_HPP
#define I_CONNECTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "ConnectionStatus.hpp"

class IConnection {
public:
    virtual ~IConnection() {}

    virtual ConnectionStatus getStatus() const = 0;

    // Queries for paint/material types table
    virtual std::vector<std::string> getPaintTypes() const = 0;
    virtual std::vector<std::string> getMaterialTypes() const = 0;
    virtual double getPaintConsumption(std::string const &, std::string const &) const = 0;

    // Queires for paint presets
    virtual std::vector<std::string> getPaintPresetsNames() const = 0;
    virtual std::vector<std::string> getPaintColumns() const = 0;
    virtual nlohmann::json getPaintPreset(std::string const &) const = 0;
	virtual nlohmann::json getPaintPresetTemplate() const = 0;

    // Queries for lacquer presets
    virtual std::vector<std::string> getLacquerPresetsNames() const = 0;
    virtual std::vector<std::string> getLacquerColumns() const = 0;
    virtual nlohmann::json getLacquerPreset(std::string const &) const = 0;
	virtual nlohmann::json getLacquerPresetTemplate() const = 0;

};

#endif
