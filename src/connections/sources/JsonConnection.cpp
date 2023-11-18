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
	for (auto it = structure.begin(); it != structure.end(); ++it) {
		std::string tableName = it.key();
		std::vector<std::string> columnNames = it.value();


		nlohmann::json composedTable;
		composedTable[PRESETS] = nlohmann::basic_json<>();

		try {
			nlohmann::json const & sourceTable = values.at(tableName);
			for (auto preset = sourceTable.begin(); preset != sourceTable.end(); ++preset) {
				nlohmann::json composedPreset;
				std::size_t count = 0;
				for (auto columnName : columnNames)
					composedPreset[columnName] = preset.value()[count++];
				composedTable[PRESETS][preset.key()] = composedPreset;
			}
		} catch (nlohmann::json_abi_v3_11_2::detail::out_of_range const &) {}

		composedTable[COLUMN_NAMES] = columnNames;

		res[tableName] = composedTable;
	}

	return res;
}

nlohmann::json decomposePresets(nlohmann::json const & data) {
	nlohmann::json res;

	for (auto table = data.begin(); table != data.end(); ++table) {
		nlohmann::json decomposedPresets;
		nlohmann::json const & presets = table.value().at(PRESETS);
		std::vector<std::string> columnNames = table.value().at(COLUMN_NAMES);
		for (auto preset = presets.begin(); preset != presets.end(); ++preset) {
			nlohmann::json values;
			for (std::string columnName : columnNames)
				values.push_back(preset.value()[columnName]);
			decomposedPresets[preset.key()] = values;
		}
		res[table.key()] = decomposedPresets;
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
	std::cout << "Preset named \"" << name << "\" created\n";
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
	std::cout << "Preset named \"" << name << "\" updated\n";
}

void removePreset(nlohmann::json & presets, std::string const & name) {
	if (presets.find(name) == presets.end())
		throw PresetDoesNotExistException(name);
	presets.erase(name);
	std::cout << "Preset named \"" << name << "\" removed\n";
}


void JsonConnection::download(bool quiet) {
	try {
		if (!quiet)
			std::cout << "Trying to download from " << _valuesFileName << "\t";

		std::ifstream structureFile(_structureFileName);
		nlohmann::json structure = nlohmann::json::parse(structureFile);
		structureFile.close();

		std::ifstream valuesFile(_valuesFileName);
		nlohmann::json values = nlohmann::json::parse(valuesFile);
		valuesFile.close();

		_data = compose(structure, values);
		_status = 0;

		if (!quiet)
			std::cout << "OK\n";
	} catch (nlohmann::json_abi_v3_11_2::detail::parse_error const & err) {
		_status = -1;
		std::cerr << err.what() << std::endl;
	}
}

void JsonConnection::upload(bool quiet) {
	if (!quiet)
		std::cout << "Trying to upload to " << _valuesFileName << "\t";
	if (isReadOnly())
		throw std::runtime_error("connection is read-only");

	std::ofstream valuesFile(_valuesFileName);
	valuesFile << decomposePresets(_data).dump(1) << '\n';
	valuesFile.close();

	if (!quiet)
		std::cout << "OK\n";
}

void JsonConnection::syncronize() {
	upload();
	download();
}

JsonConnection::JsonConnection(std::string const & structureFileName, std::string const & valueFileName, bool readOnly) : _structureFileName(structureFileName), _valuesFileName(valueFileName) {
	download();
	_readOnly = readOnly;
}

JsonConnection::~JsonConnection() {}

int JsonConnection::getStatus() const { return _status; }

bool JsonConnection::isReadOnly() const { return _readOnly; }

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
	return getPresetNames(getPresets(_data, LACQUER_CALCULATION_TABLE));
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
