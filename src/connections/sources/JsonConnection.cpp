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
#define FOIL_CALCULATION_TABLE "foil_calculation"
#define FOIL_ROLLS_TABLE "foil_rolls"

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
		nlohmann::json const & presets = table.value().at(PRESETS);
		std::vector<std::string> columnNames = table.value().at(COLUMN_NAMES);
		for (auto preset = presets.begin(); preset != presets.end(); ++preset)
			for (std::string columnName : columnNames)
				values.push_back(preset.value()[columnName]);
		res[table.key()] = values;
	}

	return res;
}

nlohmann::json & getPresets(nlohmann::json & data, std::string const & table) {
	if (data.at(table).is_null())
		throw UndefinedValueException(table);
	return data.at(table).at(PRESETS);
}
nlohmann::json const & getPresets(nlohmann::json const & data, std::string const & table) {
	if (data.at(table).is_null())
		throw UndefinedValueException(table);
	return data.at(table).at(PRESETS);
}

nlohmann::json & getPreset(nlohmann::json & presets, std::string const & name) { return presets.at(name); }
nlohmann::json & getPreset(nlohmann::json & data, std::string const & table, std::string const & name) { return getPreset(getPresets(data, table), name); }
nlohmann::json const & getPreset(nlohmann::json const & presets, std::string const & name) { return presets.at(name); }
nlohmann::json const & getPreset(nlohmann::json const & data, std::string const & table, std::string const & name) { return getPreset(getPresets(data, table), name); }

std::vector<std::string> getPresetNames(nlohmann::json const & presets) {
	std::vector<std::string> res;
	for (auto it = presets.begin(); it != presets.end(); ++it)
		res.push_back(it.key());
	return res;
}

std::map<std::string, AutoValue> convertPreset(nlohmann::json const & preset) {
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

void createPreset(nlohmann::json & presets, std::string const & name, std::map<std::string, AutoValue> const & params) {
	if (presets.find(name) != presets.end())
		throw PresetAlreadyExistsException(name);
	presets[name] = nlohmann::basic_json<>();
	for (auto it = params.begin(); it != params.end(); ++it) {
		std::string value = it->second;
		if (value.size() == 0)
			presets[name][it->first] = nlohmann::json::value_t::null;
		else
			presets[name][it->first] = value;
	}
}

void updatePreset(nlohmann::json & presets, std::string const & name, std::map<std::string, AutoValue> const & params) {
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	for (auto it = params.begin(); it != params.end(); ++it) {
		std::string value = it->second;
		if (value.size() == 0)
			presets[name][it->first] = nlohmann::json::value_t::null;
		else
			presets[name][it->first] = value;
	}
}

void removePreset(nlohmann::json & presets, std::string const & name) {
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	presets.erase(name);
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
	return getPresetNames(getPresets(_data, PAINT_CONSUMPTION_TABLE));
}
std::vector<std::string> JsonConnection::getMaterialTypes() const { return _data.at(PAINT_CONSUMPTION_TABLE).at(COLUMN_NAMES); }

double JsonConnection::getPaintConsumption(std::string const & paintType, std::string const & materialType) const {
	try {
		return getPresets(_data, PAINT_CONSUMPTION_TABLE).at(paintType).at(materialType);
	} catch (std::exception const &) {}
	throw UndefinedValueException("paint consumption of " + paintType + " with " + materialType);
}

std::vector<std::string> JsonConnection::getPaintPresetNames() const {
	return getPresetNames(getPresets(_data, PAINT_CALCULATION_TABLE));
}

std::vector<std::string> JsonConnection::getPaintPresetColumns() const { return _data.at(PAINT_CALCULATION_TABLE).at(COLUMN_NAMES); }

std::map<std::string, AutoValue> JsonConnection::getPaintPreset(std::string const & name) const {
	nlohmann::json const & preset = getPreset(_data, PAINT_CALCULATION_TABLE, name);

	if (preset.is_null())
		throw PresetDoesNotExistException(name);

	return convertPreset(preset);
}

std::map<std::string, AutoValue> JsonConnection::getPaintPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getPaintPresetColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createPaintPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	createPreset(getPresets(_data, PAINT_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::updatePaintPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	updatePreset(getPresets(_data, PAINT_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::removePaintPreset(std::string const & name) {
	removePreset(getPresets(_data, PAINT_CALCULATION_TABLE), name);
	upload();
}


// Queries for lacquer presets

std::vector<std::string> JsonConnection::getLacquerPresetNames() const {
	return getPresetNames(getPresets(_data, PAINT_CALCULATION_TABLE));
}

std::vector<std::string> JsonConnection::getLacquerPresetColumns() const { return _data.at(LACQUER_CALCULATION_TABLE).at(COLUMN_NAMES); }

std::map<std::string, AutoValue> JsonConnection::getLacquerPreset(std::string const & name) const {
	nlohmann::json const & preset = getPreset(_data, LACQUER_CALCULATION_TABLE, name);
	if (preset.is_null())
		throw PresetDoesNotExistException(name);
	return convertPreset(preset);
}

std::map<std::string, AutoValue> JsonConnection::getLacquerPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (std::string const & column : getLacquerPresetColumns())
		res[column] = NullValue();
	return res;
}

void JsonConnection::createLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	createPreset(getPresets(_data, LACQUER_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::updateLacquerPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	updatePreset(getPresets(_data, LACQUER_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::removeLacquerPreset(std::string const & name) {
	removePreset(getPresets(_data, LACQUER_CALCULATION_TABLE), name);
	upload();
}


// Queries for foil presets

std::vector<std::string> JsonConnection::getFoilPresetNames() const {
	return getPresetNames(getPresets(_data, FOIL_CALCULATION_TABLE));
}

std::vector<std::string> JsonConnection::getFoilPresetColumns() const { return _data.at(FOIL_CALCULATION_TABLE).at(COLUMN_NAMES); }

std::map<std::string, AutoValue> JsonConnection::getFoilPreset(std::string const & name) const {
	nlohmann::json const & preset = getPreset(_data, FOIL_CALCULATION_TABLE, name);
	if (preset.is_null())
		throw PresetDoesNotExistException(name);
	return convertPreset(preset);
}

std::map<std::string, AutoValue> JsonConnection::getFoilPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (auto column : getFoilPresetColumns())
		res.insert({column, NullValue()});
	return res;
}

void JsonConnection::createFoilPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	createPreset(getPresets(_data, FOIL_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::updateFoilPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	updatePreset(getPresets(_data, FOIL_CALCULATION_TABLE), name, params);
	upload();
}

void JsonConnection::removeFoilPreset(std::string const & name) {
	removePreset(getPresets(_data, FOIL_CALCULATION_TABLE), name);
	upload();
}

// Queries for foil roll presets

std::vector<std::string> JsonConnection::getFoilRollPresetNames() const {
	return getPresetNames(getPresets(_data, FOIL_ROLLS_TABLE));
}

std::vector<std::string> JsonConnection::getFoilRollPresetColumns() const { return _data.at(FOIL_ROLLS_TABLE).at(COLUMN_NAMES); }

std::map<std::string, AutoValue> JsonConnection::getFoilRollPreset(std::string const & name) const {
	nlohmann::json const & preset = getPreset(_data, FOIL_ROLLS_TABLE, name);
	if (preset.is_null())
		throw PresetDoesNotExistException(name);
	return convertPreset(preset);
}

std::map<std::string, AutoValue> JsonConnection::getFoilRollPresetTemplate() const {
	std::map<std::string, AutoValue> res;
	for (auto column : getFoilRollPresetColumns())
		res.insert({column, NullValue()});
	return res;
}

void JsonConnection::createFoilRollPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	createPreset(getPresets(_data, FOIL_ROLLS_TABLE), name, params);
	upload();
}

void JsonConnection::updateFoilRollPreset(std::string const & name, std::map<std::string, AutoValue> const & params) {
	updatePreset(getPresets(_data, FOIL_ROLLS_TABLE), name, params);
	upload();
}

void JsonConnection::removeFoilRollPreset(std::string const & name) {
	removePreset(getPresets(_data, FOIL_ROLLS_TABLE), name);
	upload();
}
