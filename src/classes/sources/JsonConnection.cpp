#include "detail/exceptions.hpp"
#include "JsonConnection.hpp"

#define PAINT_CONSUMPTION "расход краски"
#define TABLES_SECTION_NAME "tables"

template <typename T>
std::size_t getIndex(std::vector<T> const & vect, T const & value) {
	std::size_t size = vect.size();
	for (std::size_t i = 0; i < size; ++i)
		if (vect[i] == value)
			return i;
	return size;
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
	return getTable(_data, tableName)["rows"];
}

std::vector<std::string> JsonConnection::getColumnsNames(std::string const & tableName) const {
	return getTable(_data, tableName)["columns"];
}

nlohmann::json JsonConnection::getPreset(std::string const & tableName, std::size_t presetIndex) const {
	nlohmann::json res;
	nlohmann::json row = getTable(_data, tableName)["values"][presetIndex];

	std::vector<std::string> columns = getColumnsNames(tableName);
	std::size_t columnCount = columns.size();

	for (std::size_t i = 0; i < columnCount; ++i)
		res[columns[i]] = row[i];
	return res;
}

nlohmann::json JsonConnection::getPreset(std::string const & tableName, std::string const & presetName) const {
	return getPreset(tableName, getIndex(getPresetsNames(tableName), presetName));
}
