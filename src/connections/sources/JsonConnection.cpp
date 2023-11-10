#include <cstddef>
#include <string>
#include <iostream>

#include <NullValue.hpp>

#include "JsonConnection.hpp"

#include "UndefinedValueException.hpp"
#include "PresetAlreadyExistsException.hpp"
#include "PresetDoesNotExistException.hpp"

#define PAINT_CONSUMPTION_TABLE "paint_consumption"
#define PAINT_CALCULATION_TABLE "paint_calculation"
#define LACQUER_CALCULATION_TABLE "lacquer_calculation"

#define COLUMN_NAMES "column_names"
#define PRESET_NAMES "preset_names"
#define PRESETS "presets"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

nlohmann::json compose(nlohmann::json const & structure, nlohmann::json const & values) {
	nlohmann::json res;
	for (auto table = values.begin(); table != values.end(); ++table) {
		std::string tableName = table.key();
		std::vector<std::string> columnNames = structure[tableName];
		std::vector<std::string> presetNames;

		nlohmann::json composedTable;
		composedTable[PRESETS] = {};

		for (auto preset = table.value().begin(); preset != table.value().end(); ++preset) {
			presetNames.push_back(preset.key());
			nlohmann::json composedPreset;
			std::size_t count = 0;
			for (auto columnName : columnNames)
				composedPreset[columnName] = preset.value()[count++];
			composedTable[PRESETS][preset.key()] = composedPreset;
		}

		composedTable[COLUMN_NAMES] = columnNames;
		composedTable[PRESET_NAMES] = presetNames;

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

void JsonConnection::upload() {}

void JsonConnection::syncronize() {
	upload();
	download();
}

JsonConnection::JsonConnection(std::ifstream & structureFile, std::fstream & valueFile) : _structure(structureFile), _values(valueFile) { download(); }

int JsonConnection::getStatus() const { return _status; }

std::vector<std::string> JsonConnection::getPaintTypes() const { return _data[PAINT_CONSUMPTION_TABLE][PRESET_NAMES]; }
std::vector<std::string> JsonConnection::getMaterialTypes() const { return _data[PAINT_CONSUMPTION_TABLE][COLUMN_NAMES]; }

double JsonConnection::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	try {
		return _data[PAINT_CONSUMPTION_TABLE][PRESETS][paintType][materialType];
	} catch (json_type_error const &) {
		throw UndefinedValueException("paint consumption of " + paintType + " with " + materialType);
	}
}

std::vector<std::string> JsonConnection::getPaintPresetsNames() const { return _data[PAINT_CALCULATION_TABLE][PRESET_NAMES]; }

std::vector<std::string> JsonConnection::getPaintColumns() const { return _data[PAINT_CALCULATION_TABLE][COLUMN_NAMES]; }

std::map<std::string, AutoValue> JsonConnection::getPaintPreset(std::string const & name) const { return _data[PAINT_CALCULATION_TABLE][PRESETS][name]; }

std::map<std::string, AutoValue> JsonConnection::getPaintPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getPaintColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createPaintPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	if (!_data[PAINT_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetAlreadyExistsException(name);
	_data[PAINT_CALCULATION_TABLE][PRESETS][name] = data;
}

void JsonConnection::updatePaintPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	if (_data[PAINT_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetDoesNotExistException(name);
	_data[PAINT_CALCULATION_TABLE][PRESETS][name] = data;
}

void JsonConnection::removePaintPreset(std::string const & name) {
	if (_data[PAINT_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetDoesNotExistException(name);
	_data[PAINT_CALCULATION_TABLE][PRESETS].erase(name);
}


// Queries for lacquer presets

std::vector<std::string> JsonConnection::getLacquerPresetsNames() const { return _data[LACQUER_CALCULATION_TABLE][PRESET_NAMES]; }

std::vector<std::string> JsonConnection::getLacquerColumns() const { return _data[LACQUER_CALCULATION_TABLE][COLUMN_NAMES]; }

std::map<std::string, AutoValue> JsonConnection::getLacquerPreset(std::string const & name) const { return _data[LACQUER_CALCULATION_TABLE][PRESETS][name]; }

std::map<std::string, AutoValue> JsonConnection::getLacquerPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getLacquerColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	if (!_data[LACQUER_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetAlreadyExistsException(name);
	_data[LACQUER_CALCULATION_TABLE][PRESETS][name] = data;
}

void JsonConnection::updateLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & data) {
	if (_data[LACQUER_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetDoesNotExistException(name);
	_data[LACQUER_CALCULATION_TABLE][PRESETS][name] = data;
}

void JsonConnection::removeLacquerPreset(std::string const & name) {
	if (_data[LACQUER_CALCULATION_TABLE][PRESETS][name].is_null())
		throw PresetDoesNotExistException(name);
	_data[LACQUER_CALCULATION_TABLE][PRESETS].erase(name);
}
