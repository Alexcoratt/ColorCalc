#include "detail/exceptions.hpp"
#include "JsonConnection.hpp"
#include "json.hpp"
#include "json_fwd.hpp"
#include <string>

#define PAINT_CONSUMPTION "расход краски"
#define TABLES_SECTION_NAME "tables"

using json_type_error = nlohmann::json_abi_v3_11_2::detail::type_error;

template <typename T>
std::size_t getIndex(std::vector<T> const & vect, T const & value) {
	std::size_t size = vect.size();
	for (std::size_t i = 0; i < size; ++i)
		if (vect[i] == value)
			return i;
	throw std::invalid_argument("value is not found");
}

nlohmann::json & getTable(nlohmann::json data, std::string tableName) {
	try {
		return data[TABLES_SECTION_NAME][tableName];
	} catch (nlohmann::json_abi_v3_11_2::detail::type_error & err) {
		throw std::invalid_argument("table is not found");
	}
}

JsonConnection::JsonConnection(nlohmann::json const & data) : _data(data) {}
JsonConnection::JsonConnection(std::basic_fstream<char> & file) : _data(nlohmann::json::parse(file)) {}

std::vector<std::string> JsonConnection::getPaintTypes() const {
	return getTable(_data, PAINT_CONSUMPTION)["rows"];
}

std::vector<std::string> JsonConnection::getPaintTypes(std::size_t materialTypeNum) const {
	std::vector<std::string> res;

	nlohmann::json const & paintTypes = getPaintTypes();
	std::size_t rowsCount = paintTypes.size();

	for (std::size_t i = 0; i < rowsCount; ++i) {
		try {
			getPaintConsumption(i, materialTypeNum);
			res.push_back(paintTypes[i]);
		} catch (std::invalid_argument const &) {}
	}

	return res;
}

std::vector<std::string> JsonConnection::getPaintTypes(std::string const & materialTypeName) const {
	return getPaintTypes(getIndex(getMaterialTypes(), materialTypeName));
}

std::string JsonConnection::getPaintTypeName(std::size_t index) const { return getPaintTypes()[index]; }
std::size_t JsonConnection::getPaintTypeIndex(std::string const & name) const { return getIndex(getPaintTypes(), name); }


std::vector<std::string> JsonConnection::getMaterialTypes() const {
	return getTable(_data, PAINT_CONSUMPTION)["columns"];
}

std::vector<std::string> JsonConnection::getMaterialTypes(std::size_t paintTypeNum) const {
	std::vector<std::string> res;

	nlohmann::json const & materialTypes = getMaterialTypes();
	std::size_t rowsCount = materialTypes.size();

	for (std::size_t i = 0; i < rowsCount; ++i) {
		try {
			getPaintConsumption(paintTypeNum, i);
			res.push_back(materialTypes[i]);
		} catch (std::invalid_argument const &) {}
	}

	return res;
}

std::vector<std::string> JsonConnection::getMaterialTypes(std::string const & paintTypeName) const {
	return getMaterialTypes(getIndex(getPaintTypes(), paintTypeName));
}

std::string JsonConnection::getMaterialTypeName(std::size_t index) const { return getMaterialTypes()[index]; }
std::size_t JsonConnection::getMaterialTypeIndex(std::string const & name) const { return getIndex(getMaterialTypes(), name); }


double JsonConnection::getPaintConsumption(std::size_t paintTypeNum, std::size_t materialTypeNum) const {
	try {
		return getTable(_data, PAINT_CONSUMPTION)["values"][paintTypeNum][materialTypeNum];
	} catch (nlohmann::json_abi_v3_11_2::detail::type_error & err) {
		throw std::invalid_argument("value is not found");
	}
}

double JsonConnection::getPaintConsumption(std::string const & paintTypeName, std::string const & materialTypeName) const {
	auto paintTypes = getPaintTypes();
	auto materialTypes = getMaterialTypes();
	return getPaintConsumption(getIndex(paintTypes, paintTypeName), getIndex(materialTypes, materialTypeName));
}


// Queires for preset tables

std::vector<std::string> JsonConnection::getPresetsNames(std::string const & tableName) const {
	std::vector<std::string> res;
	nlohmann::json table = getTable(_data, tableName);
	std::size_t const nameColumnIndex = getPresetNameColumnIndex(tableName);

	for (nlohmann::json preset : table["rows"])
		res.push_back(preset[nameColumnIndex]);

	return res;
}

std::vector<std::string> JsonConnection::getColumnsNames(std::string const & tableName) const {
	return getTable(_data, tableName)["columns"];
}

nlohmann::json JsonConnection::getPreset(std::string const & tableName, std::size_t presetIndex) const {
	try {
		nlohmann::json res;
		nlohmann::json row = getTable(_data, tableName)["rows"][presetIndex];

		std::vector<std::string> columns = getColumnsNames(tableName);
		std::size_t columnCount = columns.size();

		for (std::size_t i = 0; i < columnCount; ++i)
			res[columns[i]] = row[i];
		return res;
	} catch (json_type_error const &) {
		throw std::invalid_argument("preset with index " + std::to_string(presetIndex) + " does not exist");
	}
}

nlohmann::json JsonConnection::getPreset(std::string const & tableName, std::string const & presetName) const {
	return getPreset(tableName, getPresetIndex(tableName, presetName));
}

std::size_t JsonConnection::getPresetIndex(std::string const & tableName, std::string const & presetName) const {
	return getIndex(getPresetsNames(tableName), presetName);
}

nlohmann::json JsonConnection::getPresetTemplate(std::string const & tableName) const {
	nlohmann::json res;
	for (std::string const & column : getColumnsNames(tableName))
		res[column] = nlohmann::json::value_t::null;
	return res;
}

std::size_t JsonConnection::getPresetNameColumnIndex(std::string const & tableName) const {
	return getTable(_data, tableName)["preset_name_column"];
}
