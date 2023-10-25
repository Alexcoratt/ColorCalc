#ifndef I_CONNECTION_HPP
#define I_CONNECTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include "json.hpp"

class IConnection {
public:
    virtual ~IConnection() {}


    // Queries for paint/material types table
    virtual std::vector<std::string> getPaintTypes() const = 0;
	virtual std::vector<std::string> getPaintTypes(std::size_t) const = 0;
    virtual std::vector<std::string> getPaintTypes(std::string const &) const = 0;
    virtual std::string getPaintTypeName(std::size_t) const = 0;
    virtual std::size_t getPaintTypeIndex(std::string const &) const = 0;

    virtual std::vector<std::string> getMaterialTypes() const = 0;
	virtual std::vector<std::string> getMaterialTypes(std::size_t) const = 0;
	virtual std::vector<std::string> getMaterialTypes(std::string const &) const = 0;
    virtual std::string getMaterialTypeName(std::size_t) const = 0;
    virtual std::size_t getMaterialTypeIndex(std::string const &) const = 0;

    virtual double getPaintConsumption(std::size_t, std::size_t) const = 0;
    virtual double getPaintConsumption(std::string const &, std::string const &) const = 0;


    // Queires for preset tables
    virtual std::vector<std::string> getPresetsNames(std::string const &) const = 0;
    virtual std::vector<std::string> getColumnsNames(std::string const &) const = 0;
	virtual nlohmann::json getPreset(std::string const &, std::size_t) const = 0;
    virtual nlohmann::json getPreset(std::string const &, std::string const &) const = 0;
    virtual std::size_t getPresetIndex(std::string const &, std::string const &) const = 0;
    virtual nlohmann::json getPresetTemplate(std::string const &) const = 0;
    virtual std::size_t getPresetNameColumnIndex(std::string const &) const = 0;
};

#endif
