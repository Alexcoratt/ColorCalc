#ifndef JSON_CONNECTION_HPP
#define JSON_CONNECTION_HPP

#include <fstream>
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
	nlohmann::json getPaintPreset(std::string const &) const;
	nlohmann::json getPaintPresetTemplate() const;
    void createPaintPreset(std::string const &, nlohmann::json const &);
    void updatePaintPreset(std::string const &, nlohmann::json const &);
    void removePaintPreset(std::string const &);

	// Queries for lacquer presets
    std::vector<std::string> getLacquerPresetsNames() const;
    std::vector<std::string> getLacquerColumns() const;
    nlohmann::json getLacquerPreset(std::string const &) const;
	nlohmann::json getLacquerPresetTemplate() const;
    void createLacquerPreset(std::string const &, nlohmann::json const &);
    void updateLacquerPreset(std::string const &, nlohmann::json const &);
    void removeLacquerPreset(std::string const &);
};

#endif
