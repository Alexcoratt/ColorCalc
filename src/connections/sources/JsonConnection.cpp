#include <cstddef>
#include <string>
#include <iostream>
#include <stdexcept>

#include <NullValue.hpp>

#include "JsonConnection.hpp"

#include "UndefinedValueException.hpp"
#include "PresetAlreadyExistsException.hpp"
#include "PresetDoesNotExistException.hpp"

#define PAINT_CONSUMPTION_TABLE "paint_consumption"
#define PAINT_CALCULATION_TABLE "paint_calculation"
#define LACQUER_CALCULATION_TABLE "lacquer_calculation"

#define COLUMN_NAMES "column_names"
#define PRESETS "presets"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

nlohmann::json compose(nlohmann::json const & structure, nlohmann::json const & values) {
	nlohmann::json res;
	for (auto table = values.begin(); table != values.end(); ++table) {
		std::string tableName = table.key();
		std::vector<std::string> columnNames = structure[tableName];

		nlohmann::json composedTable;
		composedTable[PRESETS] = {};

		for (auto preset = table.value().begin(); preset != table.value().end(); ++preset) {
			nlohmann::json composedPreset;
			std::size_t count = 0;
			for (auto columnName : columnNames)
				composedPreset[columnName] = preset.value()[count++];
			composedTable[PRESETS][preset.key()] = composedPreset;
		}

		composedTable[COLUMN_NAMES] = columnNames;

		res[tableName] = composedTable;
	}
	return res;
}

nlohmann::json decomposePresets(nlohmann::json const & data) {
	nlohmann::json res;

	for (auto table = data.begin(); table != data.end(); ++table) {
		nlohmann::json values;
		nlohmann::json const & presets = table.value()[PRESETS];
		std::vector<std::string> columnNames = table.value()[COLUMN_NAMES];
		for (auto preset = presets.begin(); preset != presets.end(); ++preset)
			for (std::string columnName : columnNames)
				values.push_back(preset.value()[columnName]);
		res[table.key()] = values;
	}

	return res;
}

void JsonConnection::download() {
	try {
		nlohmann::json structure = nlohmann::json::parse(_structure);
		nlohmann::json values = nlohmann::json::parse(_values);
		_data = compose(structure, values);
		_status = 0;
	} catch (nlohmann::json_abi_v3_11_2::detail::parse_error const & err) {
		_status = -1;
		std::cerr << err.what() << std::endl;
	}
}

// TODO: make the upload() save info to the json file
void JsonConnection::upload() {}

void JsonConnection::syncronize() {
	upload();
	download();
}

JsonConnection::JsonConnection(std::ifstream & structureFile, std::fstream & valueFile) : _structure(structureFile), _values(valueFile) { download(); }

int JsonConnection::getStatus() const { return _status; }

std::vector<std::string> JsonConnection::getPaintTypes() const {
	std::vector<std::string> res;
	nlohmann::json const & types = _data[PAINT_CONSUMPTION_TABLE][PRESETS];
	for (auto it = types.begin(); it != types.end(); ++it)
		res.push_back(it.key());
	return res;
}
std::vector<std::string> JsonConnection::getMaterialTypes() const { return _data[PAINT_CONSUMPTION_TABLE][COLUMN_NAMES]; }

double JsonConnection::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	try {
		return _data[PAINT_CONSUMPTION_TABLE][PRESETS].at(paintType).at(materialType);
	} catch (std::exception const &) {}
	throw UndefinedValueException("paint consumption of " + paintType + " with " + materialType);
}

std::vector<std::string> JsonConnection::getPaintPresetsNames() const {
	std::vector<std::string> res;
	nlohmann::json const & presets = _data[PAINT_CALCULATION_TABLE][PRESETS];
	for (auto it = presets.begin(); it != presets.end(); ++it)
		res.push_back(it.key());
	return res;
}

std::vector<std::string> JsonConnection::getPaintColumns() const { return _data[PAINT_CALCULATION_TABLE][COLUMN_NAMES]; }

std::map<std::string, AutoValue> JsonConnection::getPaintPreset(std::string const & name) const {
	nlohmann::json const & preset = _data[PAINT_CALCULATION_TABLE][PRESETS].at(name);

	if (preset.is_null())
		throw PresetDoesNotExistException(name);

	std::map<std::string, AutoValue> res;
	for (auto it = preset.begin(); it != preset.end(); ++it) {
		if (it.value().is_null())
			res[it.key()] = NullValue();
		else if (it.value().is_string())
			res[it.key()] = it.value().get<std::string>();
		else
			res[it.key()] = it.value().dump();
	}
	return res;
}

std::map<std::string, AutoValue> JsonConnection::getPaintPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getPaintColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createPaintPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	nlohmann::json & presets = _data[PAINT_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) != presets.end())
		throw PresetAlreadyExistsException(name);
	presets[name] = nlohmann::basic_json<>();
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::string value = it->second;
		if (value.size() == 0)
			presets[name][it->first] = nlohmann::json::value_t::null;
		else
			presets[name][it->first] = value;
	}

	upload();
}

void JsonConnection::updatePaintPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	nlohmann::json & presets = _data[PAINT_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::string value = it->second;
		if (value.size() == 0)
			presets[name][it->first] = nlohmann::json::value_t::null;
		else
			presets[name][it->first] = value;
	}

	upload();
}

void JsonConnection::removePaintPreset(std::string const & name) {
	nlohmann::json & presets = _data[PAINT_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	presets.erase(name);

	upload();
}


// Queries for lacquer presets

std::vector<std::string> JsonConnection::getLacquerPresetsNames() const {
	std::vector<std::string> res;
	nlohmann::json const & presets = _data[LACQUER_CALCULATION_TABLE][PRESETS];
	for (auto it = presets.begin(); it != presets.end(); ++it)
		res.push_back(it.key());
	return res;
}

std::vector<std::string> JsonConnection::getLacquerColumns() const { return _data[LACQUER_CALCULATION_TABLE][COLUMN_NAMES]; }

std::map<std::string, AutoValue> JsonConnection::getLacquerPreset(std::string const & name) const {
	nlohmann::json const & preset = _data[LACQUER_CALCULATION_TABLE][PRESETS].at(name);

	if (preset.is_null())
		throw PresetDoesNotExistException(name);

	std::map<std::string, AutoValue> res;
	for (auto it = preset.begin(); it != preset.end(); ++it) {
		if (it.value().is_null())
			res[it.key()] = NullValue();
		else if (it.value().is_string())
			res[it.key()] = it.value().get<std::string>();
		else
			res[it.key()] = it.value().dump();
	}
	return res;
}

std::map<std::string, AutoValue> JsonConnection::getLacquerPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getLacquerColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	nlohmann::json & presets = _data[LACQUER_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) != presets.end())
		throw PresetAlreadyExistsException(name);
	presets[name] = nlohmann::basic_json<>();
	for (auto it = data.begin(); it != data.end(); ++it)
		presets[name][it->first] = (std::string)it->second;

	upload();
}

void JsonConnection::updateLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	nlohmann::json & presets = _data[LACQUER_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	for (auto it = data.begin(); it != data.end(); ++it)
		presets[name][it->first] = (std::string)it->second;

	upload();
}

void JsonConnection::removeLacquerPreset(std::string const & name) {
	nlohmann::json & presets = _data[LACQUER_CALCULATION_TABLE][PRESETS];
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	presets.erase(name);

	upload();
}
