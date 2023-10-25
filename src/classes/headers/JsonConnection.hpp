#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include "IConnection.hpp"
#include <cstddef>
#include <fstream>
#include <stdexcept>

class JsonConnection : public IConnection {
private:
	nlohmann::json _data;

public:
	JsonConnection(nlohmann::json const &);
	JsonConnection(std::basic_fstream<char> &);


	// Queries for paint/material types table
	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getPaintTypes(std::size_t) const;
	std::vector<std::string> getPaintTypes(std::string const &) const;
    std::string getPaintTypeName(std::size_t) const;
    std::size_t getPaintTypeIndex(std::string const &) const;

	std::vector<std::string> getMaterialTypes() const;
	std::vector<std::string> getMaterialTypes(std::size_t) const;
	std::vector<std::string> getMaterialTypes(std::string const &) const;
    std::string getMaterialTypeName(std::size_t) const;
    std::size_t getMaterialTypeIndex(std::string const &) const;

	double getPaintConsumption(std::size_t paint, std::size_t material) const;
	double getPaintConsumption(std::string const & paint, std::string const & material) const;


	// Queires for preset tables
	std::vector<std::string> getPresetsNames(std::string const &) const;
    std::vector<std::string> getColumnsNames(std::string const &) const;
	nlohmann::json getPreset(std::string const &, std::size_t) const;
    nlohmann::json getPreset(std::string const &, std::string const &) const;
	std::size_t getPresetIndex(std::string const &, std::string const &) const;
	nlohmann::json getPresetTemplate(std::string const &) const;
    std::size_t getPresetNameColumnIndex(std::string const &) const;
};

#endif
