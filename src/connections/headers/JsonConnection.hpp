#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include <fstream>
#include <nlohmann/json.hpp>

#include "IConnection.hpp"

class JsonConnection : public IConnection {
private:
	std::ifstream & _structure;
	std::fstream & _values;
	nlohmann::json _data;
	int _status;

	void download();
	void upload();
	void syncronize();

public:
	JsonConnection(std::ifstream &, std::fstream &);

	int getStatus() const;

	// Queries for paint/material types table
	std::vector<std::string> getPaintTypes() const;
	std::vector<std::string> getMaterialTypes() const;
	double getPaintConsumption(std::string const &, std::string const &) const;

	// Queires for paint presets
	std::vector<std::string> getPaintPresetsNames() const;
    std::vector<std::string> getPaintColumns() const;
	std::map<std::string, AutoValue> getPaintPreset(std::string const &) const;
	std::map<std::string, AutoValue> getPaintPresetTemplate() const;
    void createPaintPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updatePaintPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removePaintPreset(std::string const &);

	// Queries for lacquer presets
    std::vector<std::string> getLacquerPresetsNames() const;
    std::vector<std::string> getLacquerColumns() const;
    std::map<std::string, AutoValue> getLacquerPreset(std::string const &) const;
	std::map<std::string, AutoValue> getLacquerPresetTemplate() const;
    void createLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void updateLacquerPreset(std::string const &, std::map<std::string, AutoValue> const &);
    void removeLacquerPreset(std::string const &);
};

#endif
